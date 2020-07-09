#include <vector>

#include "bib-parser/bibliography/entry-type.h"
#include "bib-parser/bibliography/field-type.h"

using std::map;
using std::string; 

namespace TUCSE
{
	std::vector<FieldType> getRequiredFieldTypes(EntryType const entryType) noexcept
	{
		// TODO: dummy
		return {
			FieldType::Address,
		};
	}

	std::vector<FieldType> getOptionalFieldTypes(EntryType const entryType) noexcept
	{
		// TODO: dummy
		return {
			FieldType::Address,
		};
	}

	std::vector<FieldType> getIgnoredFieldTypes(EntryType const entryType) noexcept
	{
		// TODO: dummy
		return {
			FieldType::Address,
		};
	}

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

} // namespace TUCSE