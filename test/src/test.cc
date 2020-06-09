#define CATCH_CONFIG_MAIN
#include <catch2/catch2.h>

#include <bib-parser/core/parser.h>

SCENARIO("Parser can be created", "[Parser]")
{
	GIVEN("An initialized Parser")
	{
		TUCSE::Parser parser = {""};
		REQUIRE(parser.getVerbose() == false);

		WHEN("Verbosity is enabled")
		{
			parser.setVerbose(true);

			THEN("Verbose will be true")
			{
				REQUIRE(parser.getVerbose() == true);
				parser.setVerbose(false); // Prevent log line from appearing when destructing
			}
		}

		WHEN("Verbosity is disabled")
		{
			parser.setVerbose(false);

			THEN("Verbose will be false")
			{
				REQUIRE(parser.getVerbose() == false);
			}
		}
	}
}
