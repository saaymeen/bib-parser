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
		reference1.addField(FieldType::Author, "Julo Berne");
		reference1.addField(FieldType::Title, "Test Title");
		reference1.addField(FieldType::Booktitle, "Booktitle Test");
		reference1.addField(FieldType::Year, "1999");


		Reference reference2{"citation2", EntryType::InBook};
		reference2.addField(FieldType::Author, "Jules Verne");
		reference2.addField(FieldType::Year, "1899");
		reference2.addField(FieldType::Editor, "Constantin Verlag");
		reference2.addField(FieldType::Title, "Buchtitel");
		reference2.addField(FieldType::Publisher, "Bad Publisher");
		reference2.addField(FieldType::Chapter, "3");
		reference2.addField(FieldType::Pages, "15--22");

		Reference reference3{"citation3", EntryType::Manual};
		reference3.addField(FieldType::Title, "Andere Sachen");

		Reference reference4{"citation4", EntryType::Article};
		reference4.addField(FieldType::Author, "Räuber Hotzenplotz");
		reference4.addField(FieldType::Title, "Bad Title");
		reference4.addField(FieldType::Journal, "Bad Journal");
		reference4.addField(FieldType::Year, "2070");

		Reference reference5{"citation5", EntryType::Book};
		reference5.addField(FieldType::Title, "Good Title");
		reference5.addField(FieldType::Author, "Lady Gaga");
		reference5.addField(FieldType::Year, "1799");

		Reference reference6{"citation6", EntryType::Manual};
		reference6.addField(FieldType::Author, "Anna Mayer");
		reference6.addField(FieldType::Year, "1699");
		reference6.addField(FieldType::Title, "Neuer Dinge");


		std::vector<Reference> references = {reference1, reference2, reference3, reference4, reference5, reference6};
		
		// ascending = a...z
		// descending = z...a
		WHEN("The vector is sorted by author descending")
		{
			Sorter sorter;
			sorter.setCriteria(Criteria::AuthorDesc);
			sorter.apply(references);

			THEN("It's elements will be rearranged accordingly")
			{
				REQUIRE(references.at(0).getCitationKey() == "citation4");
				REQUIRE(references.at(1).getCitationKey() == "citation5");
				REQUIRE(references.at(2).getCitationKey() == "citation1");
				REQUIRE(references.at(3).getCitationKey() == "citation2");
				REQUIRE(references.at(4).getCitationKey() == "citation6");
				REQUIRE(references.at(5).getCitationKey() == "citation3");
			}
		}
		
		WHEN("The vector is sorted by author ascending")
		{
			Sorter sorter;
			sorter.setCriteria(Criteria::AuthorAsc);
			sorter.apply(references);
			THEN("It's elements will be rearranged accordingly")
			{
				REQUIRE(references.at(0).getCitationKey() == "citation6");
				REQUIRE(references.at(1).getCitationKey() == "citation2");
				REQUIRE(references.at(2).getCitationKey() == "citation1");
				REQUIRE(references.at(3).getCitationKey() == "citation5");								
				REQUIRE(references.at(4).getCitationKey() == "citation4");
				REQUIRE(references.at(5).getCitationKey() == "citation3");
			}
		}
		
		WHEN("The vector is sorted by year descending")
		{
			Sorter sorter;
			sorter.setCriteria(Criteria::YearDesc);
			sorter.apply(references);

			THEN("It's elements will be rearranged accordingly")
			{
				REQUIRE(references.at(0).getCitationKey() == "citation4");
				REQUIRE(references.at(1).getCitationKey() == "citation1");
				REQUIRE(references.at(2).getCitationKey() == "citation2");
				REQUIRE(references.at(3).getCitationKey() == "citation5");
				REQUIRE(references.at(4).getCitationKey() == "citation6");
				REQUIRE(references.at(5).getCitationKey() == "citation3");
			}
		}

		WHEN("The vector is sorted by year ascending")
		{
			Sorter sorter;
			sorter.setCriteria(Criteria::YearAsc);
			sorter.apply(references);
			THEN("It's elements will be rearranged accordingly")
			{
				REQUIRE(references.at(0).getCitationKey() == "citation6");
				REQUIRE(references.at(1).getCitationKey() == "citation5");
				REQUIRE(references.at(2).getCitationKey() == "citation2");
				REQUIRE(references.at(3).getCitationKey() == "citation1");								
				REQUIRE(references.at(4).getCitationKey() == "citation4");
				REQUIRE(references.at(5).getCitationKey() == "citation3");
			}
		}

		WHEN("The vector is sorted by entryType descending") {
			Sorter sorter;
			sorter.setCriteria(Criteria::EntryTypeDesc);
			sorter.apply(references);

			THEN("It's elements will be rearranged accordingly")
			{
				REQUIRE(references.at(0).getCitationKey() == "citation3");
				REQUIRE(references.at(1).getCitationKey() == "citation6");
				REQUIRE(references.at(2).getCitationKey() == "citation1");
				REQUIRE(references.at(3).getCitationKey() == "citation2");
				REQUIRE(references.at(4).getCitationKey() == "citation5");
				REQUIRE(references.at(5).getCitationKey() == "citation4");
			}
		}

		WHEN("The vector is sorted by entryType ascending") {
			Sorter sorter;
			sorter.setCriteria(Criteria::EntryTypeAsc);
			sorter.apply(references);

			THEN("It's elements will be rearranged accordingly")
			{
				REQUIRE(references.at(0).getCitationKey() == "citation4");
				REQUIRE(references.at(1).getCitationKey() == "citation5");
				REQUIRE(references.at(2).getCitationKey() == "citation2");
				REQUIRE(references.at(3).getCitationKey() == "citation1");
				REQUIRE(references.at(4).getCitationKey() == "citation3");
				REQUIRE(references.at(5).getCitationKey() == "citation6");
			}
		}

	}
}