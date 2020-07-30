#ifndef TUCSE_BIB_PARSER_SERIALIZER_H
#define TUCSE_BIB_PARSER_SERIALIZER_H

#include <fstream>
#include <memory>
#include <unordered_map>

#include "bib-parser/bibliography/entry-type.h"
#include "bib-parser/bibliography/field-type.h"
#include "bib-parser/bibliography/reference.h"
#include "bib-parser/core/serializer-dependencies.h"
#include "bib-parser/core/types.h"
#include "bib-parser/translation/translation-table.h"

namespace TUCSE
{
	// Serializer provides functionality for writing out a list of references into a file, respecting a specific file format.
	class Serializer
	{
	public:
		// Serializer constructs a TUCSE::Serializer object with the given TUCSE::SerializerDependencies given in dependencies.
		Serializer(SerializerDependencies dependencies);

		// beginDocument should be called before the TUCSE::Reference objects will be written. It forwards the call to the file tpye specific beginDocument method initializing the output file.
		void beginDocument();
		// writeReference takes a TUCSE::Reference and forwards it to the file type specific writeReference method.
		void writeReference(Reference const &reference);
		// endDocument forwards the call to file type specific endDocument method where the output file will be finalized
		void endDocument();

		// setOutputType sets the output type for the TUCSE::Serializer object to outputType
		void setOutputType(OutputType const outputType) noexcept;
		// setTranslationTable links a translationTable to the current TUCSE::Serializer object, which will be used to fetch rules
		void setTranslationTable(std::shared_ptr<TranslationTable> translationTable) noexcept;

	private:
		void beginHTMLDocument();
		void beginXMLDocument();
		void beginPDFDocument();

		void writeHTMLReference(Reference const &reference);
		void writeXMLReference(Reference const &reference);
		void writePDFReference(Reference const &reference);

		void endHTMLDocument();
		void endXMLDocument();
		void endPDFDocument();

	private:
		std::shared_ptr<TranslationTable> translationTable{nullptr};

		OutputType outputType{OutputType::HTML};
		SerializerDependencies dependencies;

		std::unordered_map<TUCSE::EntryType, std::string> entryTypeToString = {
			{TUCSE::EntryType::Article, "Article"},
			{TUCSE::EntryType::Book, "Book"},
			{TUCSE::EntryType::Booklet, "Booklet"},
			{TUCSE::EntryType::Conference, "Conference"},
			{TUCSE::EntryType::InBook, "InBook"},
			{TUCSE::EntryType::InCollection, "InCollection"},
			{TUCSE::EntryType::InProceedings, "InProceedings"},
			{TUCSE::EntryType::Manual, "Manual"},
			{TUCSE::EntryType::MastersThesis, "MastersThesis"},
			{TUCSE::EntryType::Miscellaneous, "Miscellaneous"},
			{TUCSE::EntryType::PHDThesis, "PHDThesis"},
			{TUCSE::EntryType::Proceedings, "Proceedings"},
			{TUCSE::EntryType::TechReport, "TechReport"},
			{TUCSE::EntryType::Unpublished, "Unpublished"},
			{TUCSE::EntryType::NumberOf, "NumberOf"},
		};
		std::unordered_map<TUCSE::FieldType, std::string> fieldTypeToString = {
			{TUCSE::FieldType::Address, "Address"},
			{TUCSE::FieldType::Annote, "Annote"},
			{TUCSE::FieldType::Author, "Author"},
			{TUCSE::FieldType::Booktitle, "Booktitle"},
			{TUCSE::FieldType::Chapter, "Chapter"},
			{TUCSE::FieldType::CrossReference, "CrossReference"},
			{TUCSE::FieldType::Edition, "Edition"},
			{TUCSE::FieldType::Editor, "Editor"},
			{TUCSE::FieldType::Institution, "Institution"},
			{TUCSE::FieldType::Journal, "Journal"},
			{TUCSE::FieldType::Key, "Key"},
			{TUCSE::FieldType::Month, "Month"},
			{TUCSE::FieldType::Note, "Note"},
			{TUCSE::FieldType::Number, "Number"},
			{TUCSE::FieldType::Organization, "Organization"},
			{TUCSE::FieldType::Pages, "Pages"},
			{TUCSE::FieldType::Publisher, "Publisher"},
			{TUCSE::FieldType::School, "School"},
			{TUCSE::FieldType::Series, "Series"},
			{TUCSE::FieldType::Title, "Title"},
			{TUCSE::FieldType::Type, "Type"},
			{TUCSE::FieldType::Year, "Year"},
			{TUCSE::FieldType::NumberOf, "NumberOf"},
		};
	};

} // namespace TUCSE

#endif // TUCSE_BIB_PARSER_SERIALIZER_H