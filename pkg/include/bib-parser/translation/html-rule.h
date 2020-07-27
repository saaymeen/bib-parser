#ifndef TUCSE_BIB_PARSER_HTML_RULE_H
#define TUCSE_BIB_PARSER_HTML_RULE_H

#include <string>

#include "bib-parser/bibliography/field-type.h"
#include "bib-parser/core/types.h"
#include "bib-parser/translation/translation-table-rule.h"

namespace TUCSE
{
	// HTMLRule is a TranslationTableRule specifing how to represent the specific field type in a HTML file.
	class HTMLRule : public TranslationTableRule
	{
	public:
		// HTMLRule constructs a new object, taking into account the configuration specified by fieldType, scalarType and tag.
		HTMLRule(FieldType const fieldType, ScalarType const scalarType, HTMLTag tag)
			: tag{tag}, TranslationTableRule{fieldType, scalarType}
		{
		}

		// apply: see TUCSE::TranslationTableRule.
		void apply(SerializerDependencies &dependencies, std::string const &value) const noexcept;

	private:
		HTMLTag const tag;
	};
} // namespace TUCSE

#endif // TUCSE_BIB_PARSER_HTML_RULE_H