#ifndef TUCSE_BIB_PARSER_OUTPUT_TYPE_H
#define TUCSE_BIB_PARSER_OUTPUT_TYPE_H

#define TUCSE_BIB_PARSER_OUTPUT_TYPES HTML, PDF, XML

namespace TUCSE
{
	enum class OutputType
	{
		TUCSE_BIB_PARSER_OUTPUT_TYPES
	};

	enum class ConfigSection
	{
		TUCSE_BIB_PARSER_OUTPUT_TYPES,
		Scalars
	};

	enum class ScalarType : size_t
	{
		Number,
		Date,
		String,
		Range
	};

	enum class HTMLTag : size_t
	{
		Paragraph,
		Span,
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
} // namespace TUCSE

#endif // TUCSE_BIB_PARSER_OUTPUT_TYPE_H