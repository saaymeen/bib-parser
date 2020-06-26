#ifndef TUCSE_BIB_PARSER_ERROR_H
#define TUCSE_BIB_PARSER_ERROR_H

#include <exception>
#include <string>

namespace TUCSE
{
	class UserError : public std::exception
	{
	public:
		UserError(std::string const &message);

		std::string getMessage() const noexcept;

	private:
		std::string const message;
	};
} // namespace TUCSE

#endif // TUCSE_BIB_PARSER_ERROR_H