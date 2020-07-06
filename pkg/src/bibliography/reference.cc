#include <string>
#include <unordered_map>
#include <vector>

#include "bib-parser/bibliography/reference.h"

using std::string;
using std::unordered_map;
using std::vector;

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
	bool valid{false};
	vector<FieldType> requiredFieldTypes;

	switch (entryType)
	{
	case EntryType::Article:
		requiredFieldTypes.push_back(FieldType::Author);
		requiredFieldTypes.push_back(FieldType::Title);
		requiredFieldTypes.push_back(FieldType::Journal);
		requiredFieldTypes.push_back(FieldType::Year);
		break;

	case EntryType::Book:
		requiredFieldTypes.push_back(FieldType::Title);
		break;

	case EntryType::Booklet:
		requiredFieldTypes.push_back(FieldType::Title);
		break;

	case EntryType::Conference:
	case EntryType::InProceedings: // Same as conference
		requiredFieldTypes.push_back(FieldType::Author);
		requiredFieldTypes.push_back(FieldType::Title);
		requiredFieldTypes.push_back(FieldType::Booktitle);
		requiredFieldTypes.push_back(FieldType::Year);
		break;

	case EntryType::InBook:
		requiredFieldTypes.push_back(FieldType::Author);
		requiredFieldTypes.push_back(FieldType::Editor);
		requiredFieldTypes.push_back(FieldType::Title);
		requiredFieldTypes.push_back(FieldType::Chapter);
		requiredFieldTypes.push_back(FieldType::Pages);
		requiredFieldTypes.push_back(FieldType::Publisher);
		requiredFieldTypes.push_back(FieldType::Year);
		break;

	case EntryType::InCollection:
		requiredFieldTypes.push_back(FieldType::Author);
		requiredFieldTypes.push_back(FieldType::Title);
		requiredFieldTypes.push_back(FieldType::Booktitle);
		requiredFieldTypes.push_back(FieldType::Publisher);
		requiredFieldTypes.push_back(FieldType::Year);
		break;

	case EntryType::Manual:
		requiredFieldTypes.push_back(FieldType::Title);
		break;

	case EntryType::MastersThesis:
		requiredFieldTypes.push_back(FieldType::Author);
		requiredFieldTypes.push_back(FieldType::Title);
		requiredFieldTypes.push_back(FieldType::School);
		requiredFieldTypes.push_back(FieldType::Year);
		break;

	case EntryType::Miscellaneous:
		valid = true; // Misc does not require any specific fields
		break;

	case EntryType::PHDThesis:
		requiredFieldTypes.push_back(FieldType::Author);
		requiredFieldTypes.push_back(FieldType::Title);
		requiredFieldTypes.push_back(FieldType::School);
		requiredFieldTypes.push_back(FieldType::Year);
		break;

	case EntryType::Proceedings:
		requiredFieldTypes.push_back(FieldType::Title);
		requiredFieldTypes.push_back(FieldType::Year);
		break;

	case EntryType::TechReport:
		requiredFieldTypes.push_back(FieldType::Author);
		requiredFieldTypes.push_back(FieldType::Title);
		requiredFieldTypes.push_back(FieldType::Institution);
		requiredFieldTypes.push_back(FieldType::Year);
		break;

	case EntryType::Unpublished:
		requiredFieldTypes.push_back(FieldType::Author);
		requiredFieldTypes.push_back(FieldType::Title);
		requiredFieldTypes.push_back(FieldType::Note);
		break;

	default:
		valid = false;
		break;
	}

	if (requiredFieldTypes.empty() == false)
	{
		bool containsAll{true};
		for (auto const &requiredFieldType : requiredFieldTypes)
		{
			if (fields.count(requiredFieldType) == 0)
			{
				containsAll = false;
			}
		}

		if (containsAll)
		{
			valid = true;
		}
	}

	return valid;
}