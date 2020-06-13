#ifndef TUCSE_BIB_PARSER_SORTER_H
#define TUCSE_BIB_PARSER_SORTER_H

#include <cstddef>
#include <map>
#include <string>
#include <vector>

#include "bib-parser/bibliography/reference.h"

namespace TUCSE
{
	// REVIEW: Should the Sorter be only a namespace?
	class Sorter
	{
	public:
		enum class Criteria : size_t
		{
			NoSort = 0x00,
			AuthorAsc,
			AuthorDesc,
			CitationKeyAsc,
			CitationKeyDesc,
			EntryTypeAsc,
			EntryTypeDesc
		};

		static std::map<std::string, Criteria> const argumentMap;

	public:
		static void sort(std::vector<Reference> &references, Criteria const criteria = Criteria::NoSort) noexcept;
	};
} // namespace TUCSE

#endif // TUCSE_BIB_PARSER_SORTER_H