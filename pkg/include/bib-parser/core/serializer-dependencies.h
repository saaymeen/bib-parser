#ifndef TUCSE_BIB_PARSER_SERIALIZER_DEPENDENCIES_H
#define TUCSE_BIB_PARSER_SERIALIZER_DEPENDENCIES_H

#include <fstream>
#include <memory>
#include <string>

#include <pdfgen/pdfgen.h>

namespace TUCSE
{
	// SerializerDependencies is a data container used to pass files and other dependencies from the TUCSE::Serializer down to the TUCSE::TranslationTableRule instances being applied.
	class SerializerDependencies
	{
	public:
		// SerializerDependencies constructs an empty data container containing the dependencies for the TUCSE::Serializer.
		SerializerDependencies(std::shared_ptr<std::ofstream> outputFile, std::string const outputFilePath)
			: outputFile{outputFile}, outputFilePath{outputFilePath}
		{
		}

		// *pdfFile is a pointer to a possible PDF file being generated. Will be initialized to {nullptr} and only changed if PDF is the output type for the TUCSE::Serializer object.
		pdf_doc *pdfFile{nullptr};
		// outputFile is a shared pointer to the output file for XML and HTML file types.
		std::shared_ptr<std::ofstream> outputFile;
		// outputFilePath is the path associated with the outputFile.
		std::string const outputFilePath{};
	};
} // namespace TUCSE

#endif // TUCSE_BIB_PARSER_SERIALIZER_DEPENDENCIES_H