#ifndef TUCSE_BIB_PARSER_TRANSLATION_TABLE_H
#define TUCSE_BIB_PARSER_TRANSLATION_TABLE_H

#include <cstddef>
#include <map>
#include <string>
#include <memory>
#include <unordered_map>

#include "bib-parser/bibliography/field-type.h"
#include "bib-parser/core/xml-rule.h"
#include "bib-parser/core/pdf-rule.h"
#include "bib-parser/core/html-rule.h"
#include "bib-parser/core/types.h"

namespace TUCSE
{
	class TranslationTable
	{
	public:
		static std::map<std::string, ScalarType> const scalarTypeStrings;
		static std::map<std::string, HTMLTag> const htmlTagStrings;
		static std::map<std::string, PDFType> const pdfTypeStrings;

		std::unordered_map<FieldType, XMLRule> xmlRules;
		std::unordered_map<FieldType, PDFRule> pdfRules;
		std::unordered_map<FieldType, HTMLRule> htmlRules;

		std::unordered_map<FieldType, ScalarType> fieldScalarTypes;
		std::unordered_map<OutputType, std::unordered_map<FieldType, std::unique_ptr<TranslationTableRule>>> rules;

		void addScalarFieldType(FieldType fieldType, ScalarType scalarType) noexcept;
		void addRule(OutputType outputType, FieldType fieldType, std::unique_ptr<TranslationTableRule> translationTableRule) noexcept;
	};
} // namespace TUCSE

#endif // TUCSE_BIB_PARSER_TRANSLATION_TABLE_H