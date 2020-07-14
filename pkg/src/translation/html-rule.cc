#include "bib-parser/translation/html-rule.h"

using TUCSE::HTMLRule;
using TUCSE::SerializerDependencies;

void HTMLRule::apply(SerializerDependencies const &dependencies, std::string const &value) const noexcept
{
	*(dependencies.htmlOutputFile.get()) << "\n\t\t\t\t<div>" + value + "</div>";
}