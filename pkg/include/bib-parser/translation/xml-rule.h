#ifndef TUCSE_BIB_PARSER_XML_RULE_H
#define TUCSE_BIB_PARSER_XML_RULE_H

#include <string>

#include "bib-parser/bibliography/field-type.h"
#include "bib-parser/core/types.h"
#include "bib-parser/translation/translation-table-rule.h"

namespace TUCSE
{
	// XMLRule is a TranslationTableRule specifing how to represent the specific field type in a XML file.
	class XMLRule : public TranslationTableRule
	{
	public:
		// XMLRule constructs a new object, taking into account the configuration specified by fieldType, scalarType and tag.
		XMLRule(FieldType const fieldType, ScalarType const scalarType, std::string const tag)
			: tag{tag}, TranslationTableRule{fieldType, scalarType}
		{
		}

		// apply: see TUCSE::TranslationTableRule.
		void apply(SerializerDependencies &dependencies, std::string const &value) const noexcept;

	private:
		std::string const tag;
	};
} // namespace TUCSE

#endif // TUCSE_BIB_PARSER_XML_RULE_H