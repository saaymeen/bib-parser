#ifndef TUCSE_BIB_PARSER_PDF_RULE_H
#define TUCSE_BIB_PARSER_PDF_RULE_H

#include <string>

#include "bib-parser/translation/translation-table-rule.h"
#include "bib-parser/core/types.h"
#include "bib-parser/core/serializer-dependencies.h"
#include "bib-parser/core/types.h"
#include "bib-parser/bibliography/field-type.h"

namespace TUCSE
{
	class PDFRule : public TranslationTableRule
	{
	public:
		PDFRule(FieldType const fieldType, ScalarType const scalarType, PDFType type)
			: type{type}, TranslationTableRule{fieldType, scalarType}
		{
		}

		void apply(SerializerDependencies const &dependencies, std::string const &value) const noexcept;

	private:
		PDFType const type;
	};
} // namespace TUCSE

#endif // TUCSE_BIB_PARSER_PDF_RULE_H