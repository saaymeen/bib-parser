#ifndef TUCSE_BIB_PARSER_PARSER_H
#define TUCSE_BIB_PARSER_PARSER_H

#include <fstream>
#include <vector>

#include "bib-parser/bibliography/reference.h"
#include "bib-parser/core/sorter.h"
#include "bib-parser/core/translation-table.h"

namespace TUCSE
{
	class Parser
	{
	public:
		Parser(std::string const &inputFilePath, std::string const configFilePath = "", std::string const outputFilePath = "");

		~Parser();

		enum class OutputType
		{
			HTML,
			PDF,
			XML
		};

		enum class ConfigSection
		{
			HTML,
			PDF,
			XML,
			Common
		};

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

	private:
		std::ifstream inputFile{};
		std::ifstream configFile{};
		std::ofstream outputFile{};

		bool verbose{false};

		std::vector<Reference> references{};

		TranslationTable translationTable{};
	};
} // namespace TUCSE

#endif // TUCSE_BIB_PARSER_PARSER_H