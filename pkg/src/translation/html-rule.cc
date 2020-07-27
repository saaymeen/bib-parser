#include <exception>
#include <string>

#include "bib-parser/translation/html-rule.h"

using std::runtime_error;
using std::string;

using TUCSE::HTMLRule;
using TUCSE::SerializerDependencies;

void HTMLRule::apply(SerializerDependencies &dependencies, std::string const &value) const noexcept
{
	string htmlTag{};

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

	*(dependencies.outputFile.get()) << "\n\t\t\t\t<" + htmlTag + ">" + value + "</" + htmlTag + ">";
}