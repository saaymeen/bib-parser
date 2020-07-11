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
#include "bib-parser/translation/html-rule.h"
#include "bib-parser/translation/xml-rule.h"
#include "bib-parser/translation/pdf-rule.h"
#include "bib-parser/core/types.h"
#include "bib-parser/core/error.h"
#include "bib-parser/core/serializer.h"
#include "bib-parser/core/serializer-dependencies.h"

using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;
using TUCSE::EntryType;
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
using std::make_shared;
using std::ofstream;
using std::out_of_range;
using std::shared_ptr;
using std::to_string;

map<string, OutputType> const Parser::outputTypeMap{
	{"pdf", OutputType::PDF},
	{"xml", OutputType::XML},
	{"html", OutputType::HTML}};

Parser::Parser(string const &inputFilePath, string const configFilePath, string const outputFilePath)
	: inputFile{inputFilePath}, configFile{configFilePath}, outputFile{make_shared<ofstream>(outputFilePath)}, translationTable{make_shared<TranslationTable>()}
{
}

Parser::~Parser()
{
	VERBOSE_LOG(verbose, "Destructing Parser object, closing all related files");

	inputFile.close();
	configFile.close();
	outputFile->close();
}

void Parser::generateOutput(OutputType const outputType)
{
	VERBOSE_LOG(verbose, "Starting to generate parser output");

	// Make sure that all references are valid, throw if not
	validateReferences();

	// Initialize the serializer and pass the required dependencies for generating the output files
	SerializerDependencies serializerDependencies{outputFile};
	Serializer serializer{serializerDependencies};
	serializer.setOutputType(outputType);
	serializer.setTranslationTable(translationTable);

	// Begin the document, write all references and end the document
	serializer.beginDocument();
	for (auto const &reference : references)
	{
		serializer.writeReference(reference);
	}
	serializer.endDocument();
}

void Parser::validateReferences() const
{
	for (auto const &reference : references)
	{
		if (reference.isValid() == false)
		{
			InvalidReference invalidReference;
			throw invalidReference;
		}
	}
}

void Parser::parseConfig()
{
	VERBOSE_LOG(verbose, "Starting to parse configuration file");
	composeTranslationTable();
}

void Parser::parseInput()
{
	VERBOSE_LOG(verbose, "Starting to parse input");

	this->input = readFileString();
	this->pos = 0;

	while (tryMatch("@"))
	{
		auto dir = stringToLower(directive());
		match("{");
		if (dir == "@string")
			placeholder();
		else if (dir == "@preamble")
			preamble();
		else if (dir == "@comment")
			comment();
		else
			entry(dir);

		match("}");
	}
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
			ConfigInvalidKeyValuePair configInvalidKeyValuePair;
			throw configInvalidKeyValuePair;
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

	ConfigInvalidSection configInvalidSection;
	throw configInvalidSection;
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
		ConfigInvalidFieldType configInvalidFieldType;
		throw configInvalidFieldType;
	}

	if (section == ConfigSection::Scalars)
	{
		try
		{
			ScalarType scalarType = TranslationTable::scalarTypeStrings.at(value);
			translationTable->addScalarFieldType(fieldType, scalarType);
		}
		catch (out_of_range const &exception)
		{
			ConfigInvalidScalarType invalidScalarType;
			throw invalidScalarType;
		}
		return; // TODO: Implement goto
	}

	ScalarType scalarType{ScalarType::Date};
	try
	{
		scalarType = translationTable->getScalarType(fieldType);
	}
	catch (out_of_range const &exception)
	{
		Scalar scalar{"Test test"};
		ConfigScalarNotGiven configScalarNotGiven;
		throw scalar;
	}

	switch (section)
	{

	case ConfigSection::XML:
	{
		ScalarType scalarType = translationTable->getScalarType(fieldType);
		unique_ptr<XMLRule> xmlRule = make_unique<XMLRule>(fieldType, scalarType, value);
		translationTable->addRule(OutputType::XML, fieldType, move(xmlRule));
		break;
	}
	case ConfigSection::PDF:
	{
		try
		{
			ScalarType scalarType = translationTable->getScalarType(fieldType);
			PDFType pdfType = TranslationTable::pdfTypeStrings.at(value);
			unique_ptr<PDFRule> pdfRule = make_unique<PDFRule>(fieldType, scalarType, pdfType);
			translationTable->addRule(OutputType::PDF, fieldType, move(pdfRule));
		}
		catch (out_of_range const &exception)
		{
			ConfigInvalidPDFType configInvalidPDFType;
			throw configInvalidPDFType;
		}

		break;
	}

	case ConfigSection::HTML:
	{
		try
		{
			ScalarType scalarType = translationTable->getScalarType(fieldType);
			HTMLTag htmlTag = TranslationTable::htmlTagStrings.at(value);
			unique_ptr<HTMLRule> htmlRule = make_unique<HTMLRule>(fieldType, scalarType, htmlTag);
			translationTable->addRule(OutputType::HTML, fieldType, move(htmlRule));
		}
		catch (out_of_range const &exception)
		{
			ConfigInvalidHTMLTag configInvalidHTMLTag;
			throw configInvalidHTMLTag;
		}
		break;
	}

	default:
		ConfigInvalidConfigSection configInvalidConfigSection;
		throw configInvalidConfigSection;
	}
}
//PRIVATE FUNCTIONS

///read file into string
std::string Parser::readFileString()
{
	std::string contents((std::istreambuf_iterator<char>(this->inputFile)), std::istreambuf_iterator<char>());
	return contents;
}

/*
	#####################################################################################
	### Parsing Helper Functions
	#####################################################################################
	*/

///handles the @preamble directive
void Parser::preamble()
{
	//value could be used, but there's currently no available interface
	value();
}

///handles the @comment directive
void Parser::comment()
{
	auto start = this->pos;
	while (true)
	{
		if (this->pos == this->input.length())
		{
			ParserRunawayComment prc;
			throw prc;
		}

		if (curr() != '}')
			++this->pos;
		else
			return;
	}
}

///handles placeholders (@string directive)
void Parser::placeholder()
{
	auto kvPair = keyEqualsValue();
	if (placeholders.find(stringToLower(kvPair.first)) == placeholders.end())
		placeholders.insert(std::make_pair(stringToLower(kvPair.first), kvPair.second));
}

///handles "normal" entries
void Parser::entry(std::string dir)
{
	std::string citeKey = key(true);
	EntryType entryType;
	try
	{
		entryType = entryTypeStrings.at(dir.substr(1));
	}
	catch (out_of_range const &exception)
	{
		ParserUnknownEntryType parserUnknownEntryType;
		throw parserUnknownEntryType;
	}

	match(",");
	keyValueList(citeKey, entryType);
}

///skip whitespace (and comments) and try to find the given string WITHOUT SKIPPING NON-WHITESPACE
///return true if found, false if not found
bool Parser::tryMatch(std::string s_try_match)
{
	skipWhitespace();
	if (this->input.substr(this->pos, s_try_match.length()) == s_try_match)
		return true;
	else
		return false;
	skipWhitespace();
}

///"expect" a char
///step over the char if it is found (whitespaces are skipped), but throw an exception if not
void Parser::match(std::string s_match)
{
	skipWhitespace();
	if (this->input.substr(this->pos, s_match.length()) == s_match)
		this->pos += s_match.length();
	else
		throw UserError("Token mismatch");
	skipWhitespace();
}

///skip (ignore) whitespaces, tabs, newlines, return chars and latex comments
void Parser::skipWhitespace()
{
	//skip 'blank' space
	while (isWhitespace(curr()))
	{
		++this->pos;
	}
	//skip commented out line (marked with '%')
	if (curr() == '%')
	{
		while (curr() != '\n')
		{
			++this->pos;
		}
		//recursion to ensure every whitespace and comment is ignored
		skipWhitespace();
	}
}

///subfunction of skipWhitespace(), used to determine chars, considered as whitespaces (space, newline, etc)
bool Parser::isWhitespace(char in)
{
	const std::string whitespace = " \r\t\n";
	auto result = whitespace.find_first_of(in);
	return result != std::string::npos;
}

//shortcut for current char -> position in input string
char Parser::curr()
{
	char c;
	try
	{
		c = this->input.at(this->pos);
	}
	catch (out_of_range const &exception)
	{
		c = 0;
	}
	return c;
}

///handle value withing braces
std::string Parser::valueBraces()
{
	size_t braceCount = 0;
	match("{");
	auto start = this->pos;
	while (true)
	{
		//"state" machine to determine the depth of nesting and handle balanced braces within braces
		if (curr() == '}' && this->input.at(this->pos - 1) != '\\')
		{
			if (braceCount > 0)
				--braceCount;
			else
			{
				auto end = this->pos;
				match("}");
				return this->input.substr(start, end - start);
			}
		}
		else if (curr() == '{')
			++braceCount;
		else if (this->pos == this->input.length() - 1)
			throw UserError("Unterminated Value");

		++this->pos;
	}
}

///same as valueBraces, but with quotes
std::string Parser::valueQuotes()
{
	match("\"");
	auto start = this->pos;
	while (true)
	{
		if (curr() == '\"' && this->input[this->pos - 1] != '\\')
		{
			auto end = this->pos;
			match("\"");
			return this->input.substr(start, end - start);
		}
		else if (this->pos == this->input.length() - 1)
			throw UserError("Unterminated Value");

		++this->pos;
	}
}

///grab the next "non-structure" characters (-> the chars building the actual data)
///more precise: return those "non-structure" chars from the current pos to the pos of the next structure char
std::string Parser::key(bool caseSensitive)
{
	auto start = this->pos;
	while (true)
	{
		if (this->pos == this->input.length())
			throw UserError("Runaway Key"); //no structure char found -> key wasn't terminated

		if (keyCharMatch(curr()))
			//non-structure char -> move "cursor"
			++this->pos;
		else
			//structure char hit, return collected chars as string
			return caseSensitive ? trim(this->input.substr(start, this->pos - start)) : stringToLower(trim(this->input.substr(start, this->pos - start)));
	}
}

///bibtex uses "#" to concatenate values
///parse the values within the "#" and join them together afterwards
std::string Parser::value()
{
	std::string values = "";
	values.append(singleValue());
	while (tryMatch("#"))
	{
		match("#");
		values.append(singleValue());
	}

	//TODO: implement the value parsing properly!
	//currently, all this function does, is substituting placeholers and concatenating the pieces together
	//mutated vowel, special characters etc, are not getting parsed properly.
	//EXAMPLE: "V{\"o}lter" should be "Völter" -> this doesn't work right now.

	return values;
}

///decide how to parse the next value
std::string Parser::singleValue()
{
	auto start = this->pos;
	//if value is withing braces
	if (tryMatch("{"))
		return valueBraces();
	//if value is withing quotes
	else if (tryMatch("\""))
		return valueQuotes();
	else
	{
		//the value has neither braces nor quotes surrounding it

		auto k = key(false); //-> value
		//if k is placeholder, use placeholder to substitute
		if (this->placeholders.find(k) != this->placeholders.end())
			return placeholders.at(k);
		//if k is a number
		else if (stringIsNumber(k))
			return k;
		//value is invalid or empty
		else
			throw UserError("Unexpected Value:  " + k);
	}
}

///parse directive for later use
std::string Parser::directive()
{
	match("@");
	return "@" + key(false);
}

///parses key and value out of "key = value"-strings
std::pair<std::string, std::string> Parser::keyEqualsValue()
{
	std::string k = key(false);
	if (tryMatch("="))
	{
		match("=");
		std::string v = value();
		return std::pair<std::string, std::string>(k, v);
	}
	else
		throw UserError("... = value expected, equals sign missing:");
}

///parses the fieldList of entries using keyEqualsValue()
void Parser::keyValueList(std::string key, EntryType entryType)
{
	Reference ref = Reference(key, entryType);

	auto kvPair = keyEqualsValue();
	FieldType fieldType;

	try
	{
		fieldType = fieldTypeStrings.at(kvPair.first);
		ref.addField(fieldType, kvPair.second);
	}
	catch (out_of_range const &exception)
	{ // non-standard field types are valid, but will be ignored
	}

	while (tryMatch(","))
	{
		match(",");
		if (tryMatch("}"))
			break;
		kvPair = keyEqualsValue();

		try
		{
			fieldType = fieldTypeStrings.at(kvPair.first);
			std::unordered_map<FieldType, std::string> fields = ref.getFields();
			if (fields.find(fieldType) == fields.end())
				ref.addField(fieldType, kvPair.second);
		}
		catch (out_of_range const &exception)
		{ // non-standard field types are valid, but will be ignored
		}
	}

	//only add new reference, if the key isn't being used already
	if (!citationKeyAlreadyExists(ref.getCitationKey()))
		this->references.push_back(ref);
}

/*
	#####################################################################################
	### String Helper Funtions
	#####################################################################################
	*/

///bibtex standard requires, that if two or more entries use the same citation key, only the first one will be used further; the remaining ones will be ignored
bool Parser::citationKeyAlreadyExists(std::string key)
{
	bool exists = false;
	for (auto &ref : this->references)
		if (ref.getCitationKey() == key)
			exists = true;
	return exists;
}

///checks, whether the string consists of numbers only
bool Parser::stringIsNumber(std::string s)
{
	std::string::iterator iter = s.begin();
	while (iter != s.end() && std::isdigit(*iter))
		++iter;
	return !s.empty() && iter == s.end();
}

///checks whether the used chars are valid for bibtex-keys
bool Parser::keyCharMatch(char c)
{
	if (isalnum(c))
		return true;

	std::string disallowedChars = "\"#'(),={}%~\\";
	auto result = disallowedChars.find_first_of(c);
	return result == string::npos;
}

///uses the tolower()-function on every char of the string
std::string Parser::stringToLower(std::string input)
{
	std::string temp;
	for (std::string::iterator iter = input.begin(); iter != input.end(); ++iter)
		temp.push_back(tolower(*iter));
	return temp;
}

std::string Parser::trim(std::string input)
{
	const std::string whitespace = " \t\v\r\n";
	size_t start = input.find_first_not_of(whitespace);
	size_t end = input.find_last_not_of(whitespace);
	return start == end ? std::string() : input.substr(start, end - start + 1);
}