#ifndef TUCSE_BIB_PARSER_SORTER_H
#define TUCSE_BIB_PARSER_SORTER_H

#include <cstddef>
#include <map>
#include <string>
#include <vector>

#include "bib-parser/bibliography/reference.h"

namespace TUCSE
{
	// Sorter is utility class providing functions for sorting a std::vector of TUCSE::Reference objects according to a given criteria.
	class Sorter
	{
	public:
		// Criteria represents how a list may be sorted.
		// In general terms, Ascending means smallest to largest, 0 to 9, and/or A to Z and Descending means largest to smallest, 9 to 0, and/or Z to A.
		enum class Criteria : size_t
		{
			// NoSort means do not sort the list at all.
			NoSort = 0x00,
			// AuthorAsc sorts the list by author ascending.
			AuthorAsc,
			// AuthorDesc sorts the list by author descending.
			AuthorDesc,
			// CitationKeyAsc sorts the list by citation key ascending.
			CitationKeyAsc,
			// CitationKeyDesc sorts the list by citation key descending.
			CitationKeyDesc,
			// EntryTypeAsc sorts the list by entry type ascending.
			EntryTypeAsc,
			// EntryTypeDesc sorts the list by entry type descending.
			EntryTypeDesc,
			// YearAsc sorts the list by year ascending.
			YearAsc,
			// YearDesc sorts the list by year descending.
			YearDesc
		};

		// argumentMap maps the string value of a TUCSE::Sorter::Criteria to its matching enum value.
		static std::map<std::string, Criteria> const argumentMap;

	public:
		// setCriteria makes the sorter use the given criteria when apply() is called
		void setCriteria(Criteria const criteria) noexcept;
		// apply sorts the given vector of TUCSE::Reference objects according to the previously specified criteria.
		void apply(std::vector<Reference> &references) const;

	private:
		static bool compareAuthorAsc(Reference const &left, Reference const &right) noexcept;
		static bool compareAuthorDesc(Reference const &left, Reference const &right) noexcept;

		static bool compareEntryTypeAsc(Reference const &left, Reference const &right) noexcept;
		static bool compareEntryTypeDesc(Reference const &left, Reference const &right) noexcept;

		static bool compareYearAsc(Reference const &left, Reference const &right) noexcept;
		static bool compareYearDesc(Reference const &left, Reference const &right) noexcept;

	private:
		Criteria criteria{Criteria::NoSort};
	};
} // namespace TUCSE

#endif // TUCSE_BIB_PARSER_SORTER_H