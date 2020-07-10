#include <catch2/catch2.h>

#include <bib-parser/core/serializer.h>

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
		Reference reference1{"citation1", EntryType::InProceedings};
		reference1.addField(FieldType::Address, "Stra�e der Nationen 12");
		reference1.addField(FieldType::Year, "1999");
		reference1.addField(FieldType::Author, "author1");
		reference1.addField(FieldType::Title, "title1");
		reference1.addField(FieldType::Booktitle, "booktitle1");

		Reference reference2{"citation2", EntryType::InBook};
		reference2.addField(FieldType::CrossReference, "@reference3");
		reference2.addField(FieldType::Author, "Jules Verne");
		reference2.addField(FieldType::Year, "1899");
		reference2.addField(FieldType::Editor, "editor2");
		reference2.addField(FieldType::Title, "title2");
		reference2.addField(FieldType::Chapter, "chapter2");
		reference2.addField(FieldType::Pages, "2");
		reference2.addField(FieldType::Publisher, "publisher2");

		Reference reference3{"citation3", EntryType::Article};
		reference3.addField(FieldType::Author, "R�uber Hotzenplotz");
		reference3.addField(FieldType::Year, "2070");
		reference3.addField(FieldType::Title, "title3");
		reference3.addField(FieldType::Journal, "journal3");

		Reference reference4{"citation4", EntryType::Article};
		reference4.addField(FieldType::Author, "Lady Gaga");
		reference4.addField(FieldType::Year, "1799");
		reference4.addField(FieldType::Title, "title4");
		reference4.addField(FieldType::Journal, "journal4");

		Reference reference5{"citation5", EntryType::Conference};
		reference5.addField(FieldType::Year, "2005");
		reference5.addField(FieldType::Author, "author5");
		reference5.addField(FieldType::Title, "title5");
		reference5.addField(FieldType::Booktitle, "booktitle5");

		std::vector<Reference> references = {reference1, reference2, reference3, reference4, reference5};

		std::string htmlName = "myNewHtmlDocument";

		WHEN("the serializer creates the document")
		{
			Serializer serializer;
			serializer.createHTML(references, htmlName);

			THEN("there should be a html document in the current directory")
			{
				//...
			}
		}
	}
}