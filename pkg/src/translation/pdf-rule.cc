#include <cassert>
#include <exception>
#include <iostream>
#include <string>
#include <regex>

#include "bib-parser/translation/pdf-rule.h"

using std::regex;
using std::regex_match;
using std::regex_replace;
using std::runtime_error;
using std::smatch;
using std::string;
using std::vector;
using std::regex_constants::match_any;

using TUCSE::PDFRule;
using TUCSE::SerializerDependencies;

void PDFRule::apply(SerializerDependencies &dependencies, std::string const &value) const noexcept
{
	assert(dependencies.pdfFile);

	string formattedValue = value;

	switch (scalarType)
	{
	case ScalarType::Date:
	case ScalarType::Number:
	case ScalarType::String:
		break;
	case ScalarType::Range:
		// If the range contains a double dash, transform it, else leave
		smatch sm;
		if (regex_match(value, sm, regex("([0-9]+)--([0-9]+)")), match_any)
		{
			if (sm.size() > 2)
			{
				formattedValue = regex_replace(value, regex("([0-9]+)--([0-9]+)"), (sm[1].str() + " to " + sm[2].str()));
			}
		}
		break;
	}

	// 66 lines per page with 12pt line height = 792pt

	pdf_add_text(dependencies.pdfFile, NULL, (stringsForFieldTypes.at(fieldType) + ": " + formattedValue + "\n").c_str(), 12, 50, 20 + dependencies.pdfOffset, PDF_BLACK);
	dependencies.pdfOffset -= 12;

	if (dependencies.pdfOffset > 792) // Catch size_t overflow
	{
		dependencies.pdfOffset = 792;
		pdf_append_page(dependencies.pdfFile);
	}
}