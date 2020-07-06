#include <catch2/catch2.h>

#include <bib-parser/bibliography/serializer.h>

using TUCSE::EntryType;
using TUCSE::FieldType;
using TUCSE::Reference;
using TUCSE::Serializer;

#include <iostream>
#include <fstream>

SCENARIO("creating HTML document with Serializer class", "[Serializer]")
{
	GIVEN("An vector of valid Reference objects and the name of the html document")
	{
		Reference reference1{ "citation1", EntryType::InProceedings };
		reference1.addField(FieldType::Address, "Straﬂe der Nationen 12");
		reference1.addField(FieldType::Year, "1999");

		Reference reference2{ "citation2", EntryType::InBook };
		reference2.addField(FieldType::CrossReference, "@reference3");
		reference2.addField(FieldType::Author, "Jules Verne");
		reference2.addField(FieldType::Year, "1899");

		Reference reference3{ "citation3", EntryType::Article };
		reference3.addField(FieldType::Author, "R‰uber Hotzenplotz");
		reference3.addField(FieldType::Year, "2070");

		Reference reference4{ "citation4", EntryType::Article };
		reference4.addField(FieldType::Author, "Lady Gaga");
		reference4.addField(FieldType::Year, "1799");

		Reference reference5{ "citation5", EntryType::Article };
		reference5.addField(FieldType::Author, "anna Mayer");
		reference5.addField(FieldType::Year, "1699");


		std::vector<Reference> references = { reference1, reference2, reference3, reference4, reference5 };

		std::string htmlName = "myNewHtmlDocument";

		WHEN("the serializer creates the document")
		{
			Serializer serializer;
			serializer.createHTML(references, htmlName);

			THEN("there should be a html document in the current directory")
			{
			}
		}
	}
}