#include <map>
#include <string>

#include "bib-parser/bibliography/field-type.h"

using std::map;
using std::string;

using TUCSE::FieldType;

map<string, FieldType> const TUCSE::fieldTypeStrings{
	{"address", FieldType::Address},
	{"annote", FieldType::Annote},
	{"author", FieldType::Author},
	{"book-title", FieldType::Booktitle},
	{"chapter", FieldType::Chapter},
	{"cross-reference", FieldType::CrossReference},
	{"edition", FieldType::Edition},
	{"editor", FieldType::Editor},
	{"how-published", FieldType::HowPublished},
	{"insitution", FieldType::Institution},
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