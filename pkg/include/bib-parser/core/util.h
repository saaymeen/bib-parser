#ifndef TUCSE_BIB_PARSER_UTIL_H
#define TUCSE_BIB_PARSER_UTIL_H

#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

namespace TUCSE
{
	// splitString will return a vector of std::string objects containing the results of splitting the input string at every occurence of the delimiter char, not including the delimiter.
	std::vector<std::string> splitString(std::string const &input, char const delimiter = ' ') noexcept;

	// stringEndsWith returns true if the value ends with ending; returns false otherwise.
	inline bool stringEndsWith(std::string const &value, std::string const &ending) noexcept
	{
		if (ending.size() > value.size())
		{
			return false;
		}
		return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
	}

	// stringStartsWith returns true if the value ends with character; returns false otherwise.
	inline bool stringStartsWith(std::string const &value, char const character) noexcept
	{
		return value.rfind(character, 0) == 0;
	}

	// stringToLowercase takes a std::string object by reference and modifies it, so that all uppercase characters will be turned into their lowercase counterparts.
	inline void stringToLowercase(std::string &value) noexcept
	{
		std::transform(value.begin(), value.end(), value.begin(),
					   [](unsigned char c) { return std::tolower(c); });
	}
} // namespace TUCSE

#endif // TUCSE_BIB_PARSER_UTIL_H