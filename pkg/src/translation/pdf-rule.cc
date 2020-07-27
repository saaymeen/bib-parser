#include "bib-parser/translation/pdf-rule.h"

using TUCSE::PDFRule;
using TUCSE::SerializerDependencies;

void PDFRule::apply(SerializerDependencies &dependencies, std::string const &value) const noexcept
{
	assert(dependencies.pdfFile);

	// 66 lines per page with 12pt line height = 792pt

	pdf_add_text(dependencies.pdfFile, NULL, (value + "\n").c_str(), 12, 50, 20 + dependencies.pdfOffset, PDF_BLACK);
	dependencies.pdfOffset -= 12;

	if (dependencies.pdfOffset > 792) // Catch size_t overflow
	{
		dependencies.pdfOffset = 792;
		pdf_append_page(dependencies.pdfFile);
	}
}