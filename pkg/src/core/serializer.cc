#include "bib-parser/bibliography/reference.h"
#include "bib-parser/core/serializer.h"
#include "bib-parser/core/error.h"
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <cassert>

using TUCSE::Reference;
using TUCSE::Serializer;
using TUCSE::SerializerDependencies;
using OutputType = TUCSE::OutputType;
using TUCSE::TranslationTable;

Serializer::Serializer(SerializerDependencies const dependencies)
	: dependencies{dependencies}
{
}

void Serializer::beginDocument()
{
	switch (outputType)
	{
	case OutputType::HTML:
		beginHTMLDocument();
		break;

	default:
		SerializerUnknownOutputType suot;
		throw suot;
	}
}

void Serializer::writeReference(Reference const &reference)
{
	assert(translationTable);

	switch (outputType)
	{
	case OutputType::HTML:
		writeHTMLReference(reference);
		break;

	default:
		SerializerUnknownOutputType suot;
		throw suot;
	}
}

void Serializer::endDocument()
{
	switch (outputType)
	{
	case OutputType::HTML:
		endHTMLDocument();
		break;

	default:
		SerializerEndDocument sed;
		throw sed;
	}
}

void Serializer::beginHTMLDocument()
{
	*(dependencies.htmlOutputFile.get()) << "Hello";
}

void Serializer::writeHTMLReference(Reference const &reference)
{
}

void Serializer::endHTMLDocument()
{
	*(dependencies.htmlOutputFile.get()) << " world!";
}

void Serializer::setOutputType(OutputType const outputType) noexcept
{
	this->outputType = outputType;
}

void Serializer::setTranslationTable(std::shared_ptr<TranslationTable> translationTable) noexcept
{
	this->translationTable = translationTable;
}

bool Serializer::createHTML(std::vector<Reference> &references, std::string htmlName)
{

	for (auto const &reference : references)
	{
		if (!reference.isValid())
		{
			SerializerRefNotValid srn;
			throw srn;
		}
	}

	std::ofstream file;
	file.open(htmlName + ".html", std::fstream::out);

	for (std::vector<Reference>::size_type i = 0; i != references.size(); i++)
	{
		std::string citationKey;
		citationKey = references[i].getCitationKey();
		EntryType entryType;
		entryType = references[i].getEntryType();
		std::unordered_map fields = references[i].getFields();

		file << "<h3>" + citationKey + "</h3><br>";
		file << "<h4>" + entryTypeToString[entryType] + "</h4><br>";
		for (const auto &[fieldType, value] : fields)
		{
			file << fieldTypeToString[fieldType] + ": " + value + "<br>";
		}
		file << "<hr><br>";
	}

	file.close();
	return 0;
}