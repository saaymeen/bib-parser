#ifndef TUCSE_BIB_PARSER_PARSER_H
#define TUCSE_BIB_PARSER_PARSER_H

#include <fstream>
#include <vector>
#include <algorithm>
#include <memory>

#include "bib-parser/core/types.h"
#include "bib-parser/bibliography/reference.h"
#include "bib-parser/core/sorter.h"
#include "bib-parser/core/translation-table.h"

#define TUCSE_BIB_PARSER_OUTPUT_TYPES HTML, PDF, XML

namespace TUCSE
{
	class Parser
	{
	public:
		Parser(std::string const &inputFilePath, std::string const configFilePath = "", std::string const outputFilePath = "");

		~Parser();

		static std::map<std::string, OutputType> const outputTypeMap;

	public:
		void generateOutput(OutputType const outputType);
		void parseConfig();
		void parseInput();
		void sort(Sorter::Criteria const sortCriteria) noexcept;

		void setVerbose(bool const verbose) noexcept;
		bool getVerbose() const noexcept;

	private:
		void composeTranslationTable();
		ConfigSection getConfigSection(std::string const &value);
		void processConfigLine(std::string const &key, std::string const &value, ConfigSection const section);
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
		std::string key();
		std::string value();
		std::string singleValue();
		std::string directive();
		std::string parseFieldValue(TUCSE::FieldType, std::string); 
		std::pair<std::string, std::string> keyEqualsValue();
		void keyValueList(std::string, EntryType);
		static EntryType asEntryType(std::string);
		static FieldType asFieldType(std::string);

		bool citationKeyAlreadyExists(std::string);
		bool stringIsNumber(std::string);
		bool keyCharMatch(char);
		static std::string stringToLower(std::string);

		std::string readFileString();

	private:
		std::ifstream inputFile{};
		std::ifstream configFile{};
		std::ofstream outputFile{};

		bool verbose{false};

		enum ParserException : uint8_t
		{
			//different thingy expected
			TokenMismatch = 0x00,
			EqualSignExpected,
			UnterminatedValue,
			UnexpectedValue,

			//completely wrong
			UnknownEntryType,
			UnknwonFieldType,

			//missing brace
			RunawayKey,
			RunawayComment,

			NumberOf, // Must always be the last value in the enum
		};

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