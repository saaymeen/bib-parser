#include "bib-parser/translation/pdf-rule.h"

using TUCSE::PDFRule;
using TUCSE::SerializerDependencies;

void PDFRule::apply(SerializerDependencies &dependencies, std::string const &value) const noexcept
{
	assert(dependencies.pdfFile);

	pdf_add_text(dependencies.pdfFile, NULL, value.c_str(), 12, 50, 20 + dependencies.offset, PDF_BLACK);
	dependencies.offset += 20;
}