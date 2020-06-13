#include <catch2/catch2.h>

#include <bib-parser/bibliography/entry-type.h>
#include <bib-parser/bibliography/reference.h>

using TUCSE::EntryType;
using TUCSE::Reference;

SCENARIO("References can be created and checked for validity", "[Reference]")
{
	GIVEN("An invalid reference without any fields added")
	{
		Reference reference1{"reference1", EntryType::InProceedings};
	}
}