#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <stdexcept>

#include "bib-parser/bibliography/field-type.h"
#include "bib-parser/bibliography/reference.h"
#include "bib-parser/core/sorter.h"
#include "bib-parser/core/util.h"

using std::logic_error;
using std::map;
using std::out_of_range;
using std::runtime_error;
using std::string;
using std::vector;

using TUCSE::EntryType;
using TUCSE::Reference;
using TUCSE::Sorter;
using TUCSE::stringToLowercase;
using Criteria = TUCSE::Sorter::Criteria;
using FieldType = TUCSE::FieldType;

void Sorter::setCriteria(Criteria const criteria) noexcept
{
	this->criteria = criteria;
}

void Sorter::apply(vector<Reference> &references) const
{
	if (criteria == Criteria::NoSort)
	{
		return;
	}

	for (auto const &reference : references)
	{
		if (!reference.isValid())
		{
			throw runtime_error{"Cannot sort invalid reference with citation key: " + reference.getCitationKey()};
		}
	}

	// comparison function object (i.e. an object that satisfies the requirements of Compare)
	// which returns ​true if the first argument is less than (i.e. is ordered before) the second.
	sort(references.begin(), references.end(), [this](Reference const &left, Reference const &right) {
		switch (criteria)
		{
		case Criteria::AuthorAsc:
			return compareAuthorAsc(left, right);
		case Criteria::AuthorDesc:
			return compareAuthorDesc(left, right);
		case Criteria::YearAsc:
			return compareYearAsc(left, right);
		case Criteria::YearDesc:
			return compareYearDesc(left, right);
		case Criteria::EntryTypeAsc:
			return compareEntryTypeAsc(left, right);
		case Criteria::EntryTypeDesc:
			return compareEntryTypeDesc(left, right);
		default:
			throw logic_error{"Unknown sorting criteria provided to Sorter::apply"};
		}
		return false;
	});
}

// Return true if left's author is greater than right's author
bool Sorter::compareAuthorAsc(Reference const &left, Reference const &right) noexcept
{
	string leftValue;
	string rightValue;

	try
	{
		leftValue = left.getFieldValue(FieldType::Author);
	}
	catch (out_of_range const &exception)
	{
		return false;
	}

	try
	{
		rightValue = right.getFieldValue(FieldType::Author);
	}
	catch (out_of_range const &exception)
	{
		return true;
	}

	stringToLowercase(leftValue);
	stringToLowercase(rightValue);

	return leftValue < rightValue;
}

bool Sorter::compareAuthorDesc(Reference const &left, Reference const &right) noexcept
{
	string leftValue;
	string rightValue;

	try
	{
		leftValue = left.getFieldValue(FieldType::Author);
	}
	catch (out_of_range const &exception)
	{
		return false;
	}

	try
	{
		rightValue = right.getFieldValue(FieldType::Author);
	}
	catch (out_of_range const &exception)
	{

		return true;
	}

	stringToLowercase(leftValue);
	stringToLowercase(rightValue);

	return leftValue > rightValue;
}

bool Sorter::compareYearAsc(Reference const &left, Reference const &right) noexcept
{
	string leftValue;
	string rightValue;

	try
	{
		leftValue = left.getFieldValue(FieldType::Year);
	}
	catch (out_of_range const &exception)
	{
		return false;
	}

	try
	{
		rightValue = right.getFieldValue(FieldType::Year);
	}
	catch (std::out_of_range const &exception)
	{
		return true;
	}

	return leftValue < rightValue;
}

bool Sorter::compareYearDesc(Reference const &left, Reference const &right) noexcept
{
	string leftValue;
	string rightValue;

	try
	{
		leftValue = left.getFieldValue(FieldType::Year);
	}
	catch (out_of_range const &exception)
	{
		return false;
	}

	try
	{
		rightValue = right.getFieldValue(FieldType::Year);
	}
	catch (std::out_of_range const &exception)
	{
		return true;
	}

	return leftValue > rightValue;
}

bool Sorter::compareEntryTypeAsc(Reference const &left, Reference const &right) noexcept
{
	string leftEntryTypeString{};
	string rightEntryTypeString{};

	try
	{
		leftEntryTypeString = stringsForEntryTypes.at(left.getEntryType()); // throws out_of_range???
	}
	catch (out_of_range const &exception)
	{
		return false;
	}

	try
	{
		rightEntryTypeString = stringsForEntryTypes.at(right.getEntryType()); // throws out_of_range???
	}
	catch (out_of_range const &exception)
	{
		return true;
	}

	stringToLowercase(leftEntryTypeString);
	stringToLowercase(rightEntryTypeString);

	return leftEntryTypeString < rightEntryTypeString;
}

bool Sorter::compareEntryTypeDesc(Reference const &left, Reference const &right) noexcept
{
	string leftEntryTypeString{};
	string rightEntryTypeString{};

	try
	{
		leftEntryTypeString = stringsForEntryTypes.at(left.getEntryType()); // throws out_of_range???
	}
	catch (out_of_range const &exception)
	{
		return false;
	}

	try
	{
		rightEntryTypeString = stringsForEntryTypes.at(right.getEntryType()); // throws out_of_range???
	}
	catch (out_of_range const &exception)
	{
		return true;
	}

	stringToLowercase(leftEntryTypeString);
	stringToLowercase(rightEntryTypeString);

	// hier wird der eigentliche vergleich ausgeführt, d.h. rechts und links haben jeweils einen autor
	return leftEntryTypeString > rightEntryTypeString;
}

map<string, Sorter::Criteria> const TUCSE::Sorter::argumentMap{
	{"author-asc", Criteria::AuthorAsc},
	{"author-desc", Criteria::AuthorDesc},
	{"key-asc", Criteria::CitationKeyAsc},
	{"key-desc", Criteria::CitationKeyDesc},
	{"type-asc", Criteria::EntryTypeAsc},
	{"type-desc", Criteria::EntryTypeDesc}};
