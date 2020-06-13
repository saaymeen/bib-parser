#ifndef TUCSE_BIB_PARSER_PARSER_H
#define TUCSE_BIB_PARSER_PARSER_H

#include <fstream>
#include <vector>

#include "bib-parser/bibliography/reference.h"
#include "bib-parser/bibliography/sorter.h"

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

		static std::map<std::string, OutputType> const outputTypeMap;

	public:
		void generateOutput(OutputType const outputType);
		void parseConfig();
		void parseInput();
		void sort(Sorter::Criteria const sortCriteria) noexcept;

		void setVerbose(bool const verbose) noexcept;
		bool getVerbose() const noexcept;

	private:
		std::ifstream inputFile{};
		std::ifstream configFile{};
		std::ofstream outputFile{};

		bool verbose{false};

		std::vector<Reference> references{};
	};
} // namespace TUCSE

#endif // TUCSE_BIB_PARSER_PARSER_H