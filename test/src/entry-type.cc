#include <iostream>

#include <catch2/catch2.h>

#include <bib-parser/bibliography/entry-type.h>

SCENARIO("Reference can be created", "[Parser]")
{
	GIVEN("Some entry types")
	{
		for (uint8_t i = 0; i < TUCSE::EntryType::NumberOf; i++)
		{
			TUCSE::EntryType entryType = static_cast<TUCSE::EntryType::Value>(i);
			WHEN("An entry type is given")
			{
				THEN("It's ignored field types will not be empty")
				{
					REQUIRE(entryType.getIgnoredFieldTypes().size() > 0);
				}
			}
			WHEN("An entry type is given")
			{
				THEN("It's optional field types will not be empty")
				{
					REQUIRE(entryType.getOptionalFieldTypes().size() > 0);
				}
			}
			WHEN("An entry type is given")
			{
				THEN("It's required field types will not be empty")
				{
					REQUIRE(entryType.getRequiredFieldTypes().size() > 0);
				}
			}
		}
	}
}
