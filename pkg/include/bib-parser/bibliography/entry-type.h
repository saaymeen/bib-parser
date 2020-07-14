#ifndef TUCSE_BIB_PARSER_ENTRY_TYPE_H
#define TUCSE_BIB_PARSER_ENTRY_TYPE_H

#include <map>
#include <array>
#include <cstdint>
#include <vector>

#include "field-type.h"

namespace TUCSE
{
	enum class EntryType : size_t
	{
		Article = 0x00,
		Book,
		Booklet,
		Conference,
		InBook,
		InCollection,
		InProceedings,
		Manual,
		MastersThesis,
		Miscellaneous,
		PHDThesis,
		Proceedings,
		TechReport,
		Unpublished,

		NumberOf, // NOTE: Must always be the last value in the enum
	};

	extern std::map<std::string, EntryType> const entryTypeStrings;
	extern std::map<EntryType, std::string> const stringsForEntryTypes;

} // namespace TUCSE

#endif // TUCSE_BIB_PARSER_ENTRY_TYPE_H
