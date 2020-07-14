#include <map>
#include <string>

#include "bib-parser/bibliography/field-type.h"

using std::string;
using std::unordered_map;

using TUCSE::FieldType;

unordered_map<string, FieldType> const TUCSE::fieldTypeStrings{
	{"address", FieldType::Address},
	{"annote", FieldType::Annote},
	{"author", FieldType::Author},
	{"booktitle", FieldType::Booktitle},
	{"chapter", FieldType::Chapter},
	{"crossref", FieldType::CrossReference},
	{"edition", FieldType::Edition},
	{"editor", FieldType::Editor},
	{"howpublished", FieldType::HowPublished},
	{"institution", FieldType::Institution},
	{"journal", FieldType::Journal},
	{"key", FieldType::Key},
	{"month", FieldType::Month},
	{"note", FieldType::Note},
	{"number", FieldType::Number},
	{"organization", FieldType::Organization},
	{"pages", FieldType::Pages},
	{"publisher", FieldType::Publisher},
	{"school", FieldType::School},
	{"series", FieldType::Series},
	{"title", FieldType::Title},
	{"type", FieldType::Type},
	{"volume", FieldType::Volume},
	{"year", FieldType::Year}};

unordered_map<FieldType, string> const TUCSE::stringsForFieldTypes{
	{FieldType::Address, "address"},
	{FieldType::Annote, "annote"},
	{FieldType::Author, "author"},
	{FieldType::Booktitle, "booktitle"},
	{FieldType::Chapter, "chapter"},
	{FieldType::CrossReference, "crossref"},
	{FieldType::Edition, "edition"},
	{FieldType::Editor, "editor"},
	{FieldType::HowPublished, "howpublished"},
	{FieldType::Institution, "institution"},
	{FieldType::Journal, "journal"},
	{FieldType::Key, "key"},
	{FieldType::Month, "month"},
	{FieldType::Note, "note"},
	{FieldType::Number, "number"},
	{FieldType::Organization, "organization"},
	{FieldType::Pages, "pages"},
	{FieldType::Publisher, "publisher"},
	{FieldType::School, "school"},
	{FieldType::Series, "series"},
	{FieldType::Title, "title"},
	{FieldType::Type, "type"},
	{FieldType::Volume, "volume"},
	{FieldType::Year, "year"}};