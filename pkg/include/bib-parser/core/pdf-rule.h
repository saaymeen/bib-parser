#ifndef TUCSE_BIB_PARSER_PDF_RULE_H
#define TUCSE_BIB_PARSER_PDF_RULE_H

#include <string>

#include "bib-parser/core/translation-table-rule.h"
#include "bib-parser/core/types.h"

namespace TUCSE
{
	class PDFRule : public TranslationTableRule
	{
	public:
		PDFRule(PDFType type) : type{type}
		{
			TranslationTableRule();
		}

	private:
		PDFType const type;
	};
} // namespace TUCSE

#endif // TUCSE_BIB_PARSER_PDF_RULE_H