#include <iostream>

#include <catch2/catch2.h>

#include <bib-parser/bibliography/entry-type.h>

using TUCSE::EntryType;

SCENARIO("Reference can be created", "[Parser]")
{
	GIVEN("Some entry types")
	{
		for (size_t i = 0; i < static_cast<size_t>(EntryType::NumberOf); i++)
		{
			EntryType entryType = static_cast<EntryType>(i);
			WHEN("An entry type is given")
			{
				THEN("It's ignored field types will not be empty")
				{
				}
			}
			WHEN("An entry type is given")
			{
				THEN("It's optional field types will not be empty")
				{
				}
			}
			WHEN("An entry type is given")
			{
				THEN("It's required field types will not be empty")
				{
				}
			}
		}
	}
}
