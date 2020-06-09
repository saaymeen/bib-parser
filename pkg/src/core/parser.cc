#include "bib-parser/core/parser.h"

#include "core/log.h"

namespace TUCSE
{
	std::map<std::string, Parser::OutputType> const Parser::outputTypeMap{
		{"pdf", OutputType::PDF},
		{"xml", OutputType::XML},
		{"html", OutputType::HTML}};

	Parser::Parser(std::string const &inputFilePath, std::string const configFilePath, std::string const outputFilePath)
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
	}

	void Parser::sort(Sorter::Criteria const sortCriteria) noexcept
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
} // namespace TUCSE