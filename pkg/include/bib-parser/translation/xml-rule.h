#ifndef TUCSE_BIB_PARSER_XML_RULE_H
#define TUCSE_BIB_PARSER_XML_RULE_H

#include <string>

#include "bib-parser/bibliography/field-type.h"
#include "bib-parser/translation/translation-table-rule.h"

namespace TUCSE
{
	class XMLRule : public TranslationTableRule
	{
	public:
		XMLRule(std::string tag) : tag{tag}
		{
			TranslationTableRule();
		}

	private:
		std::string const tag;
	};
} // namespace TUCSE

#endif // TUCSE_BIB_PARSER_XML_RULE_H