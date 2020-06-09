#ifndef TUCSE_BIB_PARSER_SORTER_H
#define TUCSE_BIB_PARSER_SORTER_H

#include <map>
#include <string>

namespace TUCSE
{
	class Sorter
	{
	public:
		enum class Criteria
		{
			NoSort,
			AuthorAsc,
			AuthorDesc
		};

		static std::map<std::string, Criteria> const argumentMap;
	};
} // namespace TUCSE

#endif // TUCSE_BIB_PARSER_SORTER_H