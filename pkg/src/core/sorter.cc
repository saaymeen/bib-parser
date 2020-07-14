#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <stdexcept>

#include "bib-parser/bibliography/reference.h"
#include "bib-parser/core/sorter.h"
#include "bib-parser/core/util.h"
#include "bib-parser/bibliography/field-type.h"
#include "bib-parser/core/error.h"

using TUCSE::Reference;
using TUCSE::Sorter;
using Criteria = TUCSE::Sorter::Criteria;
using namespace std;
using TUCSE::stringToLowercase;
using FieldType = TUCSE::FieldType;
using TUCSE::EntryType;

void Sorter::setCriteria(Criteria const criteria) noexcept
{
	this->criteria = criteria;
}

void Sorter::apply(std::vector<Reference> &references) const
{
	if (criteria == Criteria::NoSort)
	{
		return;
	}

	for (auto const &reference : references)
	{
		if (!reference.isValid())
		{
			SorterRefNotValid srn;
			throw srn;
		}
	}

	sort(references.begin(), references.end(), [this](Reference const &left, Reference const &right) {
		switch (criteria)
		{
		case Criteria::AuthorAsc:
			// implementieren von compareAuthorAsc
			return compareAuthorAsc(left, right);
		case Criteria::AuthorDesc:
			// implementieren von compareAuthorDesc
			return compareAuthorDesc(left, right);
		case Criteria::YearAsc:
			return compareYearAsc(left, right);
		case Criteria::YearDesc:
			return compareYearDesc(left, right);
		case Criteria::EntryTypeAsc:
			return compareEntryTypeAsc(left, right);
		case Criteria::EntryTypeDesc:
			return compareEntryTypeDesc(left, right);
		}
		return false;
	});
}

// Return true if left's author is greater than right's author
bool Sorter::compareAuthorAsc(Reference const &left, Reference const &right) noexcept
{
	string leftValue;
	string rightValue;

	// string leftVAlue = left.getCitationKey(); // muss nicht in try catch gewrappt werden, da es immer einen gibt (noexcept)

	try
	{
		leftValue = left.getFieldValue(FieldType::Author);
	}
	catch (std::out_of_range const &exception)
	{
		// a..z sortieren, dann muss das false sein
		return false;
	}

	try
	{
		rightValue = right.getFieldValue(FieldType::Author);
	}
	catch (std::out_of_range const &exception)
	{
		// links hat autor, rechts nicht
		// im falle a...z sortieren, dann muss true sein

		// comparison function object (i.e. an object that satisfies the requirements of Compare)
		// which returns ​true if the first argument is less than (i.e. is ordered before) the second.

		// 1 2 3
		// lambda(1, 3) => true
		// 3 2 1
		// lambda(3, 1) => false
		return true;
	}

	// "codeblock vergleich" kann hier verwendet werden
	// hier wird der eigentliche vergleich ausgeführt, d.h. rechts und links haben jeweils einen autor

	// leftValue: author von left
	// rightValue: author von right

	TUCSE::stringToLowercase(leftValue);
	TUCSE::stringToLowercase(rightValue);

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
	catch (std::out_of_range const &exception)
	{
		// a..z sortieren, dann muss das false sein
		return false;
	}

	try
	{
		rightValue = right.getFieldValue(FieldType::Author);
	}
	catch (std::out_of_range const &exception)
	{
		// comparison function object (i.e. an object that satisfies the requirements of Compare)
		// which returns ​true if the first argument is less than (i.e. is ordered before) the second.
		return true;
	}

	// hier wird der eigentliche vergleich ausgeführt, d.h. rechts und links haben jeweils einen autor
	TUCSE::stringToLowercase(leftValue);
	TUCSE::stringToLowercase(rightValue);

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
	catch (std::out_of_range const &exception)
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
	catch (std::out_of_range const &exception)
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


//zur Sortierung bei doppelten EntryTypes: die Referenz, die zu erst im Referenz-Vektor steht, steht auch in der sortierten Liste zuerst
// a = "a"
// b = "a"
// a<b => 0; a<=b => 1; a>b => 0; a>=b => 1
bool Sorter::compareEntryTypeAsc(Reference const& left, Reference const& right) noexcept
{
	std::string leftEntryTypeString{};
	std::string rightEntryTypeString{};

	try
	{
		leftEntryTypeString = stringsForEntryTypes.at(left.getEntryType()); // throws out_of_range???
	}
	catch (std::out_of_range const& exception)
	{
		return false;
	}

	try
	{
		rightEntryTypeString = stringsForEntryTypes.at(right.getEntryType()); // throws out_of_range???
	}
	catch (std::out_of_range const& exception)
	{
		return true;
	}

	TUCSE::stringToLowercase(leftEntryTypeString);
	TUCSE::stringToLowercase(rightEntryTypeString);

	return leftEntryTypeString < rightEntryTypeString;
}

bool Sorter::compareEntryTypeDesc(Reference const& left, Reference const& right) noexcept
{
	std::string leftEntryTypeString{};
	std::string rightEntryTypeString{};

	try
	{
		leftEntryTypeString = stringsForEntryTypes.at(left.getEntryType()); // throws out_of_range???
	}
	catch (std::out_of_range const& exception)
	{
		return false;
	}

	try
	{
		rightEntryTypeString = stringsForEntryTypes.at(right.getEntryType()); // throws out_of_range???
	}
	catch (std::out_of_range const& exception)
	{
		return true;
	}

	TUCSE::stringToLowercase(leftEntryTypeString);
	TUCSE::stringToLowercase(rightEntryTypeString);

	// hier wird der eigentliche vergleich ausgeführt, d.h. rechts und links haben jeweils einen autor
	return leftEntryTypeString > rightEntryTypeString;
}

std::map<std::string, Sorter::Criteria> const TUCSE::Sorter::argumentMap{
	{"author-asc", Criteria::AuthorAsc},
	{"author-desc", Criteria::AuthorDesc},
	{"key-asc", Criteria::CitationKeyAsc},
	{"key-desc", Criteria::CitationKeyDesc},
	{"type-asc", Criteria::EntryTypeAsc},
	{"type-desc", Criteria::EntryTypeDesc}};
