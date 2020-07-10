#ifndef TUCSE_BIB_PARSER_HTML_RULE_H
#define TUCSE_BIB_PARSER_HTML_RULE_H

#include <string>

#include "bib-parser/core/types.h"
#include "bib-parser/translation/translation-table-rule.h"

namespace TUCSE
{
	class HTMLRule : public TranslationTableRule
	{
	public:
		HTMLRule(HTMLTag tag) : tag{tag}
		{
			TranslationTableRule();
		}

	private:
		HTMLTag const tag;
	};
} // namespace TUCSE

#endif // TUCSE_BIB_PARSER_HTML_RULE_H