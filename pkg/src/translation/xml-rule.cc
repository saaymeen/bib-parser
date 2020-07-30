#include <exception>
#include <iostream>
#include <string>
#include <regex>

#include "bib-parser/translation/xml-rule.h"

using std::regex;
using std::regex_match;
using std::regex_replace;
using std::runtime_error;
using std::smatch;
using std::string;
using std::vector;
using std::regex_constants::match_any;

using TUCSE::SerializerDependencies;
using TUCSE::XMLRule;

void XMLRule::apply(SerializerDependencies &dependencies, std::string const &value) const noexcept
{
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

	*(dependencies.outputFile.get()) << "\n\t\t<" + tag + ">" + formattedValue + "</" + tag + ">";
}