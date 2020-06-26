#include <map>
#include <iostream>
#include <vector>
#include <memory>
#include <exception>

#include "bib-parser/core/util.h"
#include "bib-parser/core/sorter.h"
#include "bib-parser/core/parser.h"
#include "core/log.h"
#include "bib-parser/bibliography/field-type.h"
#include "bib-parser/core/html-rule.h"
#include "bib-parser/core/xml-rule.h"
#include "bib-parser/core/pdf-rule.h"
#include "bib-parser/core/types.h"
#include "bib-parser/core/error.h"

using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;
using TUCSE::Parser;
using OutputType = TUCSE::OutputType;
using Criteria = TUCSE::Sorter::Criteria;
using TUCSE::splitString;
using TUCSE::stringEndsWith;
using TUCSE::stringStartsWith;
using ConfigSection = TUCSE::ConfigSection;
using ScalarType = TUCSE::ScalarType;
using std::make_unique;
using std::move;
using std::unique_ptr;
using PDFType = TUCSE::PDFType;
using HTMLTag = TUCSE::HTMLTag;
using std::out_of_range;
using TUCSE::UserError;

map<string, OutputType> const Parser::outputTypeMap{
	{"pdf", OutputType::PDF},
	{"xml", OutputType::XML},
	{"html", OutputType::HTML}};

Parser::Parser(string const &inputFilePath, string const configFilePath, string const outputFilePath)
	: inputFile{inputFilePath}, configFile{configFilePath}, outputFile{outputFilePath}
{
}

Parser::~Parser()
{
	VERBOSE_LOG(verbose, "Destructing Parser object, closing all related files");

	inputFile.close();
	configFile.close();
	outputFile.close();
}

void Parser::generateOutput(OutputType const outputType)
{
	VERBOSE_LOG(verbose, "Starting to generate parser output");
}

void Parser::parseConfig()
{
	VERBOSE_LOG(verbose, "Starting to parse configuration file");
	composeTranslationTable();
}

void Parser::parseInput()
{
	VERBOSE_LOG(verbose, "Starting to parse input");
}

void Parser::sort(Criteria const sortCriteria) noexcept
{
	VERBOSE_LOG(verbose, "Starting to sort references");
}

void Parser::setVerbose(bool const verbose) noexcept
{
	this->verbose = verbose;
}

bool Parser::getVerbose() const noexcept
{
	return verbose;
}

void Parser::composeTranslationTable()
{
	ConfigSection section{ConfigSection::Scalars};
	string line;
	size_t lineNumber = 0;
	while (getline(configFile, line))
	{
		lineNumber += 1;

		// ignore comments
		if (stringStartsWith(line, '#'))
		{
			continue;
		}

		// ignore empty lines
		if (line.empty())
		{
			continue;
		}

		// handle sections
		if (stringStartsWith(line, '[') && stringEndsWith(line, "]"))
		{
			section = getConfigSection(line.substr(1, line.size() - 2));
			continue;
		}

		// handle key value pairs
		vector<string> parts = splitString(line, '=');
		if (parts.size() != 2)
		{
			UserError userError{"Error parsing config file: Invalid key value pair in line " + lineNumber};
			throw userError;
		}

		processConfigLine(parts[0], parts[1], section);
	}
}

ConfigSection Parser::getConfigSection(string const &value)
{
	if (value == "scalars")
	{
		return ConfigSection::Scalars;
	}
	else if (value == "html")
	{
		return ConfigSection::HTML;
	}
	else if (value == "xml")
	{
		return ConfigSection::XML;
	}
	else if (value == "pdf")
	{
		return ConfigSection::PDF;
	}

	UserError userError{"Error parsing config file: Invalid section found: \"" + value + "\""};
	throw userError;
}

void Parser::processConfigLine(string const &key, string const &value, ConfigSection const section)
{
	FieldType fieldType{FieldType::Address};
	try
	{
		fieldType = fieldTypeStrings.at(key);
	}
	catch (out_of_range const &exception)
	{
		UserError userError{"Error parsing config file: Invalid field type \"" + key + "\""};
		throw userError;
	}

	switch (section)
	{
	case ConfigSection::Scalars:
	{
		try
		{
			ScalarType scalarType = TranslationTable::scalarTypeStrings.at(value);
			translationTable.addScalarFieldType(fieldType, scalarType);
		}
		catch (out_of_range const &exception)
		{
			UserError userError{"Error parsing config file: Invalid scalar type \"" + value + "\""};
			throw userError;
		}

		break;
	}

	case ConfigSection::XML:
	{
		unique_ptr<XMLRule> xmlRule = make_unique<XMLRule>(value);
		translationTable.addRule(OutputType::XML, fieldType, move(xmlRule));
		break;
	}
	case ConfigSection::PDF:
	{
		try
		{
			PDFType pdfType = TranslationTable::pdfTypeStrings.at(value);
			unique_ptr<PDFRule> pdfRule = make_unique<PDFRule>(pdfType);
			translationTable.addRule(OutputType::PDF, fieldType, move(pdfRule));
		}
		catch (out_of_range const &exception)
		{
			UserError userError{"Error parsing config file: Invalid PDF type \"" + value + "\""};
			throw userError;
		}

		break;
	}

	case ConfigSection::HTML:
	{
		try
		{
			HTMLTag htmlTag = TranslationTable::htmlTagStrings.at(value);
			unique_ptr<HTMLRule> htmlRule = make_unique<HTMLRule>(htmlTag);
			translationTable.addRule(OutputType::HTML, fieldType, move(htmlRule));
		}
		catch (out_of_range const &exception)
		{
			UserError userError{"Error parsing config file: Invalid HTML tag \"" + value + "\""};
			throw userError;
		}
		break;
	}

	default:
		throw new std::exception{};
	}
}