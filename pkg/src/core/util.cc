#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "bib-parser/core/util.h"

using std::string;
using std::stringstream;
using std::vector;

vector<string> TUCSE::splitString(string const &input, char const delimiter) noexcept
{
	stringstream stringStream{input};
	string token;
	vector<string> parts;

	while (getline(stringStream, token, delimiter))
	{
		parts.push_back(token);
	}

	return parts;
}