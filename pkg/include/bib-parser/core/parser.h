#ifndef TUCSE_BIB_PARSER_PARSER_H
#define TUCSE_BIB_PARSER_PARSER_H

#include <algorithm>
#include <fstream>
#include <memory>
#include <vector>

#include "bib-parser/bibliography/reference.h"
#include "bib-parser/core/sorter.h"
#include "bib-parser/core/types.h"
#include "bib-parser/translation/translation-table.h"

namespace TUCSE
{
	// Parser represents the core of the library by providing functionality to check and read a .bib file, perform operations on it and transform it into an output file.
	class Parser
	{
	public:
		// Parser constructs an initialized parser object.
		Parser(std::string const &inputFilePath, std::string const configFilePath = "", std::string const outputFilePath = "");
		// ~Parser destructs the parser object, closing all files generated in the constructor
		~Parser();

		// outputTypeMap maps the string representation of an TUCSE::OutputType to the corresponding enum value.
		static std::map<std::string, OutputType> const outputTypeMap;

	public:
		// generateOutput is a wrapper around a TUCSE::Serializer object. It writes all the allocated TUCSE::Reference objects into the output file, respecting the given outputType.
		void generateOutput(OutputType const outputType);
		// parseConfig goes through the given config file in .ini format and generates TUCSE::TranslationTableRule objects which will be used by generateOutput later.
		void parseConfig();
		// parseInput checks if the given bib file is in the correct format and generates a list of TUCSE::Reference objects based on the entries provided by it.
		void parseInput();
		// sort is a wrapper around a TUCSE::Sorter object. It will sort the list of TUCSE::Reference objects with respect to the given criteria.
		void sort(Sorter::Criteria const sortCriteria) noexcept;

		// setVerbose enables or disables verbose mode for the TUCSE::Parser object.
		void setVerbose(bool const verbose) noexcept;
		// getVerbose return true if the TUCSE::Parser object is currently in verbose mode; returns false otherwise.
		bool getVerbose() const noexcept;

	private:
		// composeTranslationTable is responsible for populating the TUCSE::TranslationTable object with the rules obtained from the style file
		void composeTranslationTable();
		// getConfigSection translates a string given in value into the corresponsing TUCSE::ConfigSection value.
		ConfigSection getConfigSection(std::string const &value);
		// processConfigLine parses a single line from the given config file.
		void processConfigLine(std::string const &key, std::string const &value, ConfigSection const section);
		// validateReferences assures that all TUCSE::Reference objects stored in the TUCSE::Parser object are valid. Throws an exception if not.
		void validateReferences() const;

		void preamble();
		void comment();
		void placeholder();
		void entry(std::string);
		bool tryMatch(std::string);
		void match(std::string);
		void skipWhitespace();
		static bool isWhitespace(char);
		char curr();
		std::string valueBraces();
		std::string valueQuotes();
		std::string key(bool);
		std::string value();
		std::string singleValue();
		std::string directive();
		std::string parseFieldValue(std::string);
		std::pair<std::string, std::string> keyEqualsValue();
		void keyValueList(std::string, EntryType);

		bool citationKeyAlreadyExists(std::string);
		bool stringIsNumber(std::string);
		std::string trim(std::string);
		bool keyCharMatch(char);
		static std::string stringToLower(std::string);

		std::string readFileString();

	private:
		std::ifstream inputFile{};
		std::ifstream configFile{};
		std::shared_ptr<std::ofstream> outputFile{};

		std::string const outputFilePath{};

		bool verbose{false};

		std::vector<Reference> references{};

		//used for storing bibtex "variables" -> placeholders  => @string{key = "value"}
		std::unordered_map<std::string, std::string> placeholders =
			{
				{"jan", "January"},
				{"feb", "February"},
				{"mar", "March"},
				{"apr", "April"},
				{"may", "May"},
				{"jun", "June"},
				{"jul", "July"},
				{"aug", "August"},
				{"sep", "September"},
				{"oct", "October"},
				{"nov", "November"},
				{"dec", "December"},
				{"january", "January"},
				{"february", "February"},
				{"march", "March"},
				{"april", "April"},
				{"may", "May"},
				{"june", "June"},
				{"july", "July"},
				{"august", "August"},
				{"september", "September"},
				{"october", "October"},
				{"november", "November"},
				{"december", "December"},
		};

		//text of input file
		std::string input;
		//position "cursor" in input file
		size_t pos;

		std::shared_ptr<TranslationTable> translationTable;
	};
} // namespace TUCSE

#endif // TUCSE_BIB_PARSER_PARSER_H