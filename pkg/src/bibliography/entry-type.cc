#include <vector>

#include "bib-parser/bibliography/entry-type.h"
#include "bib-parser/bibliography/field-type.h"

using std::map;
using std::string;

namespace TUCSE
{
	map<string, EntryType> const entryTypeStrings{
		{"article", EntryType::Article},
		{"book", EntryType::Book},
		{"booklet", EntryType::Booklet},
		{"conference", EntryType::Conference},
		{"inbook", EntryType::InBook},
		{"incollection", EntryType::InCollection},
		{"inproceedings", EntryType::InProceedings},
		{"manual", EntryType::Manual},
		{"mastersthesis", EntryType::MastersThesis},
		{"misc", EntryType::Miscellaneous},
		{"phdthesis", EntryType::PHDThesis},
		{"proceedings", EntryType::Proceedings},
		{"techreport", EntryType::TechReport},
		{"unpublished", EntryType::Unpublished}};

	map<EntryType, string> const stringsForEntryTypes{
		{EntryType::Article, "article"},
		{EntryType::Book, "book"},
		{EntryType::Booklet, "booklet"},
		{EntryType::Conference, "conference"},
		{EntryType::InBook, "inbook"},
		{EntryType::InCollection, "incollection"},
		{EntryType::InProceedings, "inproceedings"},
		{EntryType::Manual, "manual"},
		{EntryType::MastersThesis, "mastersthesis"},
		{EntryType::Miscellaneous, "misc"},
		{EntryType::PHDThesis, "phdthesis"},
		{EntryType::Proceedings, "proceedings"},
		{EntryType::TechReport, "techreport"},
		{EntryType::Unpublished, "unpublished"}};

} // namespace TUCSE