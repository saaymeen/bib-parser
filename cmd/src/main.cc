#include <exception>
#include <fstream>
#include <iostream>
#include <string>

#include <cli11/cli11.h>

#include <bib-parser/core/error.h>
#include <bib-parser/core/parser.h>
#include <bib-parser/core/sorter.h>

using std::cout;
using std::endl;
using std::string;

using CLIApp = CLI::App;
using TUCSE::OutputType;
using TUCSE::Parser;
using Criteria = TUCSE::Sorter::Criteria;

// runCheckApp is the entry point for the `check` subcommand used to check an input file for validity.
int runCheckApp(std::string const &inputFilePath, bool const verbose);

// runConvertApp is the entry point for the `convert` subcommand used to convert an input file into the desired output
int runConvertApp(std::string const &inputFilePath, std::string const &outputFilePath, std::string const &configFilePath, TUCSE::Sorter::Criteria const &sortCriteria, TUCSE::OutputType const &outputType, bool const verbose);

// Error collects useful error codes used as return value for the main function
enum Error
{
	// ErrorNone means the app has run without any error
	ErrorNone = 0x00,
	// ErrorNoSubcommand means the user supplied no subcommand to the app
	ErrorNoSubcommand = 0x01,
	// ErrorException means an exception has occured and further information will be printed to stdout
	ErrorException = 0x02,
};

int main(int argc, char **argv)
{
	string inputFilePath{""};
	string configFilePath{""};
	string outputFilePath{""};

	Criteria sortCriteria{Criteria::NoSort};
	OutputType outputType{OutputType::HTML};

	bool verbose{false};

	CLIApp app{"Parse and modify some nice stuff"};
	app.require_subcommand(1);
	app.add_flag("-v,--verbose", verbose, "Output recurring information about the application state.");

	CLIApp *convertApp = app.add_subcommand("convert", "Convert a BibTeX file to other file formats.");
	CLIApp *checkApp = app.add_subcommand("check", "Check a BibTeX file for semantic errors.");

	convertApp->add_option<std::string, std::string>("-i,--input", inputFilePath, "Path to the input file containing BibTeX definitions.")->required();
	convertApp->add_option<std::string, std::string>("-o,--output", outputFilePath, "Path pointing to where the output file will be put.")->required();
	convertApp->add_option<std::string, std::string>("-c,--config", configFilePath, "Path to the configuration file containing translation rules for semantic tags.")->required();
	convertApp->add_option("-t,--type", outputType, "XML, PDF or HTML")->required()->transform(CLI::CheckedTransformer(TUCSE::Parser::outputTypeMap, CLI::ignore_case));
	convertApp->add_option("-s,--sort", sortCriteria, "Can be used to sort the BibTeX entries.")->transform(CLI::CheckedTransformer(TUCSE::Sorter::argumentMap, CLI::ignore_case));

	checkApp->add_option<std::string, std::string>("-i,--input", inputFilePath, "Path to the input file containing BibTeX definitions.")->required();

	CLI11_PARSE(app, argc, argv); // Throws if invalid arguments supplied

	if (*checkApp)
	{
		return runCheckApp(inputFilePath, verbose);
	}
	else if (*convertApp)
	{
		return runConvertApp(inputFilePath, outputFilePath, configFilePath, sortCriteria, outputType, verbose);
	}

	return ErrorNoSubcommand;
}

int runCheckApp(std::string const &inputFilePath, bool const verbose)
{
	Parser parser{inputFilePath};
	parser.setVerbose(verbose);

	try
	{
		parser.parseInput();
	}
	catch (std::exception &e)
	{
		cout << e.what() << endl;
		return ErrorException;
	}

	cout << "Input file is valid" << endl;
	return ErrorNone;
}

int runConvertApp(std::string const &inputFilePath, std::string const &outputFilePath, std::string const &configFilePath, TUCSE::Sorter::Criteria const &sortCriteria, TUCSE::OutputType const &outputType, bool const verbose)
{
	Parser parser{inputFilePath, configFilePath, outputFilePath};
	parser.setVerbose(verbose);

	try
	{
		parser.parseConfig();
		parser.parseInput();

		if (sortCriteria != TUCSE::Sorter::Criteria::NoSort)
		{
			parser.sort(sortCriteria);
		}

		parser.generateOutput(outputType);
	}
	catch (std::exception &e)
	{
		cout << e.what() << endl;
		return ErrorException;
	}

	return ErrorNone;
}