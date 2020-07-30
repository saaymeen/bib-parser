#include <exception>
#include <iostream>
#include <string>
#include <regex>

#include "bib-parser/core/util.h"
#include "bib-parser/translation/html-rule.h"

using std::regex;
using std::regex_match;
using std::regex_replace;
using std::runtime_error;
using std::smatch;
using std::string;
using std::vector;
using std::regex_constants::match_any;

using TUCSE::HTMLRule;
using TUCSE::SerializerDependencies;
using TUCSE::splitString;

void HTMLRule::apply(SerializerDependencies &dependencies, std::string const &value) const noexcept
{
	string htmlTag{};
	string formattedValue = value;

	switch (tag)
	{
	case HTMLTag::Heading1:
		htmlTag = "h1";
		break;
	case HTMLTag::Heading2:
		htmlTag = "h2";
		break;
	case HTMLTag::Heading3:
		htmlTag = "h3";
		break;
	case HTMLTag::Heading4:
		htmlTag = "h4";
		break;
	case HTMLTag::Heading5:
		htmlTag = "h5";
		break;
	case HTMLTag::Heading6:
		htmlTag = "h6";
		break;
	case HTMLTag::Paragraph:
		htmlTag = "p";
		break;
	case HTMLTag::Span:
		htmlTag = "span";
		break;
	default:
		htmlTag = "?";
		break;
	}

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

	*(dependencies.outputFile.get()) << "\n\t\t\t\t<" + htmlTag + " class=\"" + stringsForFieldTypes.at(fieldType) + "\">" + formattedValue + "</" + htmlTag + ">";
}