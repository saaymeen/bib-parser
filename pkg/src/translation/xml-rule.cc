#include "bib-parser/translation/xml-rule.h"

using TUCSE::SerializerDependencies;
using TUCSE::XMLRule;

void XMLRule::apply(SerializerDependencies &dependencies, std::string const &value) const noexcept
{
	*(dependencies.outputFile.get()) << value + " = = " + tag + "\n";
}