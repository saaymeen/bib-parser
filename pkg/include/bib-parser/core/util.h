#ifndef TUCSE_BIB_PARSER_UTIL_H
#define TUCSE_BIB_PARSER_UTIL_H

#include <vector>
#include <string>

namespace TUCSE
{
	std::vector<std::string> splitString(std::string const &input, char const delimiter = ' ') noexcept;

	inline bool stringEndsWith(std::string const &value, std::string const &ending) noexcept
	{
		if (ending.size() > value.size())
		{
			return false;
		}
		return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
	}

	inline bool stringStartsWith(std::string const &value, char const character) noexcept
	{
		return value.rfind(character, 0) == 0;
	}
} // namespace TUCSE

#endif // TUCSE_BIB_PARSER_UTIL_H