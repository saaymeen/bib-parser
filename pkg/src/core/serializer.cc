#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <cassert>
#include <memory>
#include <unordered_map>
#include <exception>

#include "bib-parser/bibliography/reference.h"
#include "bib-parser/core/serializer.h"
#include "bib-parser/core/error.h"

using std::out_of_range;
using TUCSE::Reference;
using TUCSE::Serializer;
using TUCSE::SerializerDependencies;
using OutputType = TUCSE::OutputType;
using std::shared_ptr;
using std::unordered_map;
using TUCSE::TranslationTable;
using FieldType = TUCSE::FieldType;
using std::string;

namespace
{
	char const *const HTMLBegin = "<!doctype html>\n<html lang=\"en\">\n\t<head>\n\t\t<meta charset=\"utf-8\" />\n\n\t\t<title>BIB Entries</title>\n\t\t<meta name=\"description\" content=\"Parsed with BIB Parser\" />\n\t\t<meta name=\"author\" content=\"Group 2\" />\n\t</head>\n\n\t<body>\n\t\t<ul class=\"references\">";
	char const *const HTMLEnd = "\n\t\t</ul>\n\t</body>\n</html>";

	char const *const XMLBegin = "XMLBEGIN";
	char const *const XMLEnd = "XMLEND";
} // namespace

Serializer::Serializer(SerializerDependencies dependencies)
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

	case OutputType::XML:
		beginXMLDocument();
		break;

	case OutputType::PDF:
		beginPDFDocument();
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

	case OutputType::XML:
		writeXMLReference(reference);
		break;

	case OutputType::PDF:
		writePDFReference(reference);
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

	case OutputType::XML:
		endXMLDocument();
		break;

	case OutputType::PDF:
		endPDFDocument();
		break;

	default:
		SerializerEndDocument sed;
		throw sed;
	}
}

void Serializer::beginHTMLDocument()
{
	*(dependencies.outputFile.get()) << HTMLBegin;
}

void Serializer::beginXMLDocument()
{
	*(dependencies.outputFile.get()) << XMLBegin;
}

void Serializer::beginPDFDocument()
{
	pdf_info pdfInfo = {
		.creator = "TU Chemnitz",
		.producer = "BIB-Parser",
		.title = "Reference List",
		.author = "TU Chemnitz",
		.subject = "References",
		.date = "Today",
	};
	dependencies.pdfFile = pdf_create(PDF_A4_WIDTH, PDF_A4_HEIGHT, &pdfInfo);
	pdf_set_font(dependencies.pdfFile, "Times-Roman");
	pdf_append_page(dependencies.pdfFile);
}

void Serializer::writeHTMLReference(Reference const &reference)
{
	assert(translationTable);

	EntryType entryType = reference.getEntryType();

	// TODO: Wrap in try catch
	// TODO: What to do when reference is opened, but rules are not found...?
	// -> Buffer the file output, and write only if no exception is found...?
	*(dependencies.outputFile.get()) << "\n\t\t\t<li class=\"reference " + stringsForEntryTypes.at(entryType) + " id=\"" + reference.getCitationKey() + "\">";

	unordered_map<FieldType, string> referenceFields = reference.getFields();
	for (auto const &referenceField : referenceFields)
	{
		std::string fieldTypeString{"unknown"};
		try
		{
			fieldTypeString = stringsForFieldTypes.at(referenceField.first);
			auto rule = translationTable->getRule(OutputType::HTML, referenceField.first);

			// Rule found
			rule->apply(dependencies, referenceField.second);
		}
		catch (out_of_range const &exception)
		{
			throw std::runtime_error{"No translation rule found for field: " + fieldTypeString};
		}
	}
	*(dependencies.outputFile.get()) << "\n\t\t\t</li>";
}

void Serializer::writeXMLReference(Reference const &reference)
{
	assert(translationTable);

	EntryType entryType = reference.getEntryType();

	// TODO: Wrap in try catch
	// TODO: What to do when reference is opened, but rules are not found...?
	// -> Buffer the file output, and write only if no exception is found...?
	*(dependencies.outputFile.get()) << "\n\t\t\t<reference entry-type=\"reference " + stringsForEntryTypes.at(entryType) + " citation-key=\"" + reference.getCitationKey() + "\">";

	unordered_map<FieldType, string> referenceFields = reference.getFields();
	for (auto const &referenceField : referenceFields)
	{
		std::string fieldTypeString{"unknown"};
		try
		{
			fieldTypeString = stringsForFieldTypes.at(referenceField.first);
			auto rule = translationTable->getRule(OutputType::XML, referenceField.first);

			// Rule found
			rule->apply(dependencies, referenceField.second);
		}
		catch (out_of_range const &exception)
		{
			throw std::runtime_error{"No translation rule found for field: " + fieldTypeString};
		}
	}
	*(dependencies.outputFile.get()) << "\n\t\t\t</reference>";
}

void Serializer::writePDFReference(Reference const &reference)
{
	assert(dependencies.pdfFile);

	assert(translationTable);

	EntryType entryType = reference.getEntryType();
	unordered_map<FieldType, string> referenceFields = reference.getFields();
	for (auto const &referenceField : referenceFields)
	{
		std::string fieldTypeString{"unknown"};
		try
		{
			fieldTypeString = stringsForFieldTypes.at(referenceField.first);
			auto rule = translationTable->getRule(OutputType::PDF, referenceField.first);

			// Rule found
			rule->apply(dependencies, referenceField.second);
		}
		catch (out_of_range const &exception)
		{
			std::cout << "Helle\n";
			throw std::runtime_error{"No translation rule found for field: " + fieldTypeString};
		}
	}
}

void Serializer::endHTMLDocument()
{
	*(dependencies.outputFile.get()) << HTMLEnd;
}

void Serializer::endXMLDocument()
{
	*(dependencies.outputFile.get()) << XMLEnd;
}

void Serializer::endPDFDocument()
{
	assert(dependencies.pdfFile);

	pdf_save(dependencies.pdfFile, dependencies.outputFilePath.c_str());
	pdf_destroy(dependencies.pdfFile);
	dependencies.pdfFile = nullptr;
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