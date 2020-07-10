#ifndef TUCSE_BIB_PARSER_TRANSLATION_TABLE_H
#define TUCSE_BIB_PARSER_TRANSLATION_TABLE_H

#include <cstddef>
#include <map>
#include <string>
#include <memory>
#include <unordered_map>

#include "bib-parser/bibliography/field-type.h"
#include "bib-parser/translation/xml-rule.h"
#include "bib-parser/translation/pdf-rule.h"
#include "bib-parser/translation/html-rule.h"
#include "bib-parser/core/types.h"

namespace TUCSE
{
	class TranslationTable
	{
	public:
		static std::map<std::string, ScalarType> const scalarTypeStrings;
		static std::map<std::string, HTMLTag> const htmlTagStrings;
		static std::map<std::string, PDFType> const pdfTypeStrings;

	private:
		std::unordered_map<FieldType, ScalarType> scalarFieldTypes;
		std::unordered_map<OutputType, std::unordered_map<FieldType, std::shared_ptr<TranslationTableRule>>> rules;

	public:
		void addScalarFieldType(FieldType fieldType, ScalarType scalarType) noexcept;
		void addRule(OutputType const outputType, FieldType const fieldType, std::shared_ptr<TranslationTableRule> translationTableRule) noexcept;
		ScalarType getScalarType(FieldType const fieldType) const;
		std::shared_ptr<TranslationTableRule> getRule(OutputType const outputType, FieldType const fieldType) const;
	};
} // namespace TUCSE

#endif // TUCSE_BIB_PARSER_TRANSLATION_TABLE_H