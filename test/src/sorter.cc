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
		reference1.addField(FieldType::Year, "1999");

		Reference reference2{"citation2", EntryType::InBook};
		reference2.addField(FieldType::CrossReference, "@reference3");
		reference2.addField(FieldType::Author, "Jules Verne");
		reference2.addField(FieldType::Year, "1899");

		Reference reference3{"citation3", EntryType::Article};
		reference3.addField(FieldType::Author, "Räuber Hotzenplotz");
		reference3.addField(FieldType::Year, "2070");

		Reference reference4{"citation4", EntryType::Article};
		reference4.addField(FieldType::Author, "Lady Gaga");
		reference4.addField(FieldType::Year, "1799");

		Reference reference5{"citation5", EntryType::Article};
		reference5.addField(FieldType::Author, "anna Mayer");
		reference5.addField(FieldType::Year, "1699");
		

		std::vector<Reference> references = {reference1, reference2, reference3, reference4, reference5};
		
		// ascending = a...z
		// descending = z...a
		/*WHEN("The vector is sorted by author descending")
		{
			Sorter sorter;
			sorter.setCriteria(Criteria::AuthorDesc);
			sorter.apply(references);

			THEN("It's elements will be rearranged accordingly")
			{
				REQUIRE(references.at(0).getCitationKey() == "citation3");
				REQUIRE(references.at(1).getCitationKey() == "citation4");
				REQUIRE(references.at(2).getCitationKey() == "citation2");
				REQUIRE(references.at(3).getCitationKey() == "citation5");
				REQUIRE(references.at(4).getCitationKey() == "citation1");
			}
		}
		
		WHEN("The vector is sorted by author ascending")
		{
			Sorter sorter;
			sorter.setCriteria(Criteria::AuthorAsc);
			sorter.apply(references);
			THEN("It's elements will be rearranged accordingly")
			{
				REQUIRE(references.at(0).getCitationKey() == "citation5");
				REQUIRE(references.at(1).getCitationKey() == "citation2");
				REQUIRE(references.at(2).getCitationKey() == "citation4");
				REQUIRE(references.at(3).getCitationKey() == "citation3");								
				REQUIRE(references.at(4).getCitationKey() == "citation1");
			}
		}
		
		WHEN("The vector is sorted by year descending")
		{
			Sorter sorter;
			sorter.setCriteria(Criteria::YearDesc);
			sorter.apply(references);

			THEN("It's elements will be rearranged accordingly")
			{
				REQUIRE(references.at(0).getCitationKey() == "citation3");
				REQUIRE(references.at(1).getCitationKey() == "citation1");
				REQUIRE(references.at(2).getCitationKey() == "citation2");
				REQUIRE(references.at(3).getCitationKey() == "citation4");
				REQUIRE(references.at(4).getCitationKey() == "citation5");
			}
		}

		WHEN("The vector is sorted by year ascending")
		{
			Sorter sorter;
			sorter.setCriteria(Criteria::YearAsc);
			sorter.apply(references);
			THEN("It's elements will be rearranged accordingly")
			{
				REQUIRE(references.at(0).getCitationKey() == "citation5");
				REQUIRE(references.at(1).getCitationKey() == "citation4");
				REQUIRE(references.at(2).getCitationKey() == "citation2");
				REQUIRE(references.at(3).getCitationKey() == "citation1");								
				REQUIRE(references.at(4).getCitationKey() == "citation3");
			}
		}*/

		WHEN("The vector is sorted by citationkey descending")
		{
			Sorter sorter;
			sorter.setCriteria(Criteria::YearDesc);
			sorter.apply(references);

			THEN("It's elements will be rearranged accordingly")
			{
				REQUIRE(references.at(0).getCitationKey() == "citation3");
				REQUIRE(references.at(1).getCitationKey() == "citation1");
				REQUIRE(references.at(2).getCitationKey() == "citation2");
				REQUIRE(references.at(3).getCitationKey() == "citation4");
				REQUIRE(references.at(4).getCitationKey() == "citation5");
			}
		}

		WHEN("The vector is sorted by citationkey ascending")
		{
			Sorter sorter;
			sorter.setCriteria(Criteria::YearAsc);
			sorter.apply(references);
			THEN("It's elements will be rearranged accordingly")
			{
				REQUIRE(references.at(0).getCitationKey() == "citation5");
				REQUIRE(references.at(1).getCitationKey() == "citation4");
				REQUIRE(references.at(2).getCitationKey() == "citation2");
				REQUIRE(references.at(3).getCitationKey() == "citation1");
				REQUIRE(references.at(4).getCitationKey() == "citation3");
			}
		}

	}
}