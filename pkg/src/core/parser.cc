#include <map>
#include <iostream>
#include <vector>

#include "bib-parser/core/util.h"
#include "bib-parser/core/sorter.h"
#include "bib-parser/core/parser.h"
#include "core/log.h"
#include "bib-parser/bibliography/field-type.h"
#include "bib-parser/core/html-rule.h"
#include "bib-parser/core/xml-rule.h"
#include "bib-parser/core/pdf-rule.h"

using std::map;
using std::string;
using std::vector;
using TUCSE::Parser;
using OutputType = TUCSE::Parser::OutputType;
using Criteria = TUCSE::Sorter::Criteria;
using TUCSE::splitString;
using TUCSE::stringEndsWith;
using TUCSE::stringStartsWith;
using ConfigSection = TUCSE::Parser::ConfigSection;

map<string, OutputType> const outputTypeMap{
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
}

void Parser::parseInput()
{
	VERBOSE_LOG(verbose, "Starting to parse input");

	composeTranslationTable();
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
	ConfigSection section{ConfigSection::Common};
	string line;
	while (getline(configFile, line))
	{
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
			section = getConfigSection(line.substr(1, line.size() - 1));
			continue;
		}

		// handle key value pairs
		vector<string> parts = splitString(line, '=');
		if (parts.size() != 2)
		{
			throw new std::exception{};
		}

		processConfigLine(parts[0], parts[1], section);
	}
}

ConfigSection Parser::getConfigSection(string const &value)
{
	if (value == "common")
	{
		return ConfigSection::Common;
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

	throw new std::exception{};
}

void Parser::processConfigLine(string const &key, string const &value, ConfigSection const section)
{
	// TODO: throws out of bound exception, how to handle error
	FieldType const fieldType = fieldTypeStrings.at(key);

	TUCSE::HTMLRule rule;

	switch (section)
	{
	case ConfigSection::Common:

		break;
	case ConfigSection::XML:
		break;
	case ConfigSection::PDF:
		break;
	case ConfigSection::HTML:
		break;
	}
}