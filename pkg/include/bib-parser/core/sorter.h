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
			EntryTypeDesc,
			YearAsc,
			YearDesc
		};

		static std::map<std::string, Criteria> const argumentMap;

	public:
		void setCriteria(Criteria const criteria) noexcept;
		void apply(std::vector<Reference> &references) const;

	private:
		static bool compareAuthorAsc(Reference const &left, Reference const &right) noexcept;
		static bool compareAuthorDesc(Reference const &left, Reference const &right) noexcept;

		static bool compareEntryTypeAsc(Reference const &left, Reference const &right) noexcept;
		static bool compareEntryTypeDesc(Reference const &left, Reference const &right) noexcept;

		static bool compareYearAsc(Reference const &left, Reference const &right) noexcept;
		static bool compareYearDesc(Reference const &left, Reference const &right) noexcept;

		static bool compareCitationKeyAsc(Reference const &left, Reference const &right) noexcept;
		static bool compareCitationKeyDesc(Reference const &left, Reference const &right) noexcept;



	private:
		Criteria criteria{Criteria::NoSort};
	};
} // namespace TUCSE

#endif // TUCSE_BIB_PARSER_SORTER_H