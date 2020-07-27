#ifndef TUCSE_BIB_PARSER_PDF_RULE_H
#define TUCSE_BIB_PARSER_PDF_RULE_H

#include <string>

#include "bib-parser/bibliography/field-type.h"
#include "bib-parser/core/serializer-dependencies.h"
#include "bib-parser/core/types.h"
#include "bib-parser/translation/translation-table-rule.h"

namespace TUCSE
{
	// PDFRule is a TranslationTableRule specifing how to represent the specific field type in a PDF file.
	class PDFRule : public TranslationTableRule
	{
	public:
		// PDFRule constructs a new object, taking into account the configuration specified by fieldType, scalarType and type.
		PDFRule(FieldType const fieldType, ScalarType const scalarType, PDFType type)
			: type{type}, TranslationTableRule{fieldType, scalarType}
		{
		}

		// apply: see TUCSE::TranslationTableRule.
		void apply(SerializerDependencies &dependencies, std::string const &value) const noexcept;

	private:
		PDFType const type;
	};
} // namespace TUCSE

#endif // TUCSE_BIB_PARSER_PDF_RULE_H