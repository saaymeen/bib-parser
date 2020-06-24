#ifndef TUCSE_BIB_PARSER_TRANSLATION_TABLE_H
#define TUCSE_BIB_PARSER_TRANSLATION_TABLE_H

#include <cstddef>
#include <map>
#include <string>

namespace TUCSE
{
	class TranslationTable
	{
		enum class ScalarType : size_t
		{
			Number,
			Date,
			String
		};

		enum class HTMLTag : size_t
		{
			Paragraph,
			Heading1,
			Heading2,
			Heading3,
			Heading4,
			Heading5,
			Heading6
		};

		enum class PDFType : size_t
		{
			Title,
			Text
		};

		static std::map<std::string, ScalarType> const scalarTypeStrings;
		static std::map<std::string, HTMLTag> const htmlTagStrings;
		static std::map<std::string, PDFType> const pdfTypeStrings;
	};
} // namespace TUCSE

#endif // TUCSE_BIB_PARSER_TRANSLATION_TABLE_H