#include <exception>
#include <string>

#include "bib-parser/core/error.h"

using std::exception;
using std::string;

using TUCSE::UserError;

UserError::UserError(string const &message) : message{message}
{
}

string UserError::getMessage() const noexcept
{
	return message;
}