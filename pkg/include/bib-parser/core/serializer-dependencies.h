#ifndef TUCSE_BIB_PARSER_SERIALIZER_DEPENDENCIES_H
#define TUCSE_BIB_PARSER_SERIALIZER_DEPENDENCIES_H

#include <fstream>
#include <memory>
#include <string>

#include <pdfgen/pdfgen.h>

namespace TUCSE
{
	class SerializerDependencies
	{
	public:
		SerializerDependencies(std::shared_ptr<std::ofstream> outputFile, std::string const outputFilePath)
			: outputFile{outputFile}, outputFilePath{outputFilePath}
		{
		}

		pdf_doc *pdfFile{nullptr};
		std::shared_ptr<std::ofstream> outputFile;
		std::string const outputFilePath{};

		uint64_t offset{0};
	};
} // namespace TUCSE

#endif // TUCSE_BIB_PARSER_SERIALIZER_DEPENDENCIES_H