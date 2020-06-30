#include <string>
#include <unordered_map>

#include "bib-parser/bibliography/reference.h"

using std::string;
using std::unordered_map;

using TUCSE::EntryType;
using TUCSE::FieldType;
using TUCSE::Reference;

Reference::Reference(string const &citationKey, EntryType const entryType)
	: citationKey{citationKey}, entryType{entryType}, fields{} {};

EntryType Reference::getEntryType() const noexcept
{
	return entryType;
}

void Reference::addField(FieldType const fieldType, string const &value) noexcept
{
	fields.insert({fieldType, value});
}

string Reference::getCitationKey() const noexcept
{
	return citationKey;
}

unordered_map<FieldType, string> Reference::getFields() const noexcept
{
	return fields;
}

std::string Reference::getFieldValue(FieldType const fieldType) const
{
	return fields.at(fieldType);
}

bool Reference::isValid() const noexcept
{
	// TODO: Implement
	return true;
}