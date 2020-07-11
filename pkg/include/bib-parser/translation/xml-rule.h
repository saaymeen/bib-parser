#ifndef TUCSE_BIB_PARSER_XML_RULE_H
#define TUCSE_BIB_PARSER_XML_RULE_H

#include <string>

#include "bib-parser/bibliography/field-type.h"
#include "bib-parser/translation/translation-table-rule.h"
#include "bib-parser/core/types.h"
#include "bib-parser/bibliography/field-type.h"

namespace TUCSE
{
	class XMLRule : public TranslationTableRule
	{
	public:
		XMLRule(FieldType const fieldType, ScalarType const scalarType, std::string const tag)
			: tag{tag}, TranslationTableRule{fieldType, scalarType}
		{
		}

		void apply(SerializerDependencies const &dependencies, std::string const &value) const noexcept;

	private:
		std::string const tag;
	};
} // namespace TUCSE

#endif // TUCSE_BIB_PARSER_XML_RULE_H