#ifndef TUCSE_BIB_PARSER_SERIALIZER_H
#define TUCSE_BIB_PARSER_SERIALIZER_H

#include "bib-parser/bibliography/reference.h"
#include "bib-parser/bibliography/entry-type.h"
#include "bib-parser/bibliography/field-type.h"
#include <fstream>
#include <unordered_map>

namespace TUCSE
{
	class Serializer
	{
	public:
		bool createHTML(std::vector<Reference> &references, std::string htmlName);

	private:
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