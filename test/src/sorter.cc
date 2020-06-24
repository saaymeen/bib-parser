#include <catch2/catch2.h>

#include <bib-parser/bibliography/entry-type.h>
#include <bib-parser/bibliography/field-type.h>
#include <bib-parser/bibliography/reference.h>
#include <bib-parser/core/sorter.h>

using TUCSE::EntryType;
using TUCSE::FieldType;
using TUCSE::Reference;
using TUCSE::Sorter;
using Criteria = TUCSE::Sorter::Criteria;
#include <iostream>

SCENARIO("Sorting Reference objects with the Sorter class", "[Sorter]")
{
	GIVEN("An vector of valid, unordered Reference objects")
	{
		Reference reference1{"citation1", EntryType::InProceedings};
		reference1.addField(FieldType::Address, "Straße der Nationen 12");

		Reference reference2{"citation2", EntryType::InBook};
		reference2.addField(FieldType::CrossReference, "@reference3");
		reference2.addField(FieldType::Author, "Jules Verne");

		Reference reference3{"citation3", EntryType::Article};
		reference3.addField(FieldType::Month, "July");
		reference3.addField(FieldType::Author, "Räuber Hotzenplotz");

		std::vector<Reference> references = {reference1, reference2, reference3};

		WHEN("The vector is sorted by author descending")
		{
			Sorter sorter;
			sorter.setCriteria(Criteria::AuthorDesc);
			sorter.apply(references);
			THEN("It's elements will be rearranged accordingly")
			{
				REQUIRE(references.at(0).getCitationKey() == "citation1");
				REQUIRE(references.at(1).getCitationKey() == "citation3");
				REQUIRE(references.at(2).getCitationKey() == "citation2");
			}
		}

		WHEN("The vector is sorted by author ascending")
		{
			Sorter sorter;
			sorter.setCriteria(Criteria::AuthorAsc);
			sorter.apply(references);
			THEN("It's elements will be rearranged accordingly")
			{
				REQUIRE(references.at(0).getCitationKey() == "citation2");
				REQUIRE(references.at(1).getCitationKey() == "citation3");
				REQUIRE(references.at(2).getCitationKey() == "citation1");
			}
		}
	}
}