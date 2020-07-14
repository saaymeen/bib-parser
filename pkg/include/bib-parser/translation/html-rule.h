#ifndef TUCSE_BIB_PARSER_HTML_RULE_H
#define TUCSE_BIB_PARSER_HTML_RULE_H

#include <string>

#include "bib-parser/core/types.h"
#include "bib-parser/translation/translation-table-rule.h"
#include "bib-parser/bibliography/field-type.h"

namespace TUCSE
{
	class HTMLRule : public TranslationTableRule
	{
	public:
		HTMLRule(FieldType const fieldType, ScalarType const scalarType, HTMLTag tag)
			: tag{tag}, TranslationTableRule{fieldType, scalarType}
		{
		}

		void apply(SerializerDependencies const &dependencies, std::string const &value) const noexcept;

	private:
		HTMLTag const tag;
	};
} // namespace TUCSE

#endif // TUCSE_BIB_PARSER_HTML_RULE_H