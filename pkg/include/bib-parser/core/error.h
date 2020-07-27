/* OBSOLETE
#ifndef TUCSE_BIB_PARSER_ERROR_H
#define TUCSE_BIB_PARSER_ERROR_H

#include <exception>
#include <string>
#include <cstdio>

#define MAKE_STATIC_EXCEPTION(NAME, WHAT)                         \
	class NAME : public std::exception                            \
	{                                                             \
	public:                                                       \
		virtual const char *what() const throw() { return WHAT; } \
	}

#define MAKE_DYNAMIC_EXCEPTION(NAME)                                 \
	class NAME : public std::exception                               \
	{                                                                \
	public:                                                          \
		NAME(char const *message) : message{message} {}              \
		virtual const char *what() const throw() { return message; } \
                                                                     \
	private:                                                         \
		char const *message;                                         \
	}

namespace TUCSE
{
	// TODO: Remove user error
	class UserError : public std::exception
	{
		std::string message;

	public:
		UserError(std::string message) : message{message} {}

		virtual const char *what() const throw() { return message.c_str(); }
	};

	MAKE_STATIC_EXCEPTION(InvalidReference, "Invalid reference found");

	MAKE_STATIC_EXCEPTION(ConfigInvalidKeyValuePair, "Invalid key valud pair");
	MAKE_STATIC_EXCEPTION(ConfigInvalidSection, "Invalid section found");
	MAKE_STATIC_EXCEPTION(ConfigInvalidFieldType, "Invalid field type");
	MAKE_STATIC_EXCEPTION(ConfigInvalidScalarType, "Invalid scalar type");
	MAKE_STATIC_EXCEPTION(ConfigScalarNotGiven, "Scalar type not given");
	MAKE_STATIC_EXCEPTION(ConfigInvalidPDFType, "Invalid PDF type");
	MAKE_STATIC_EXCEPTION(ConfigInvalidHTMLTag, "Invalid HTML tag");
	MAKE_STATIC_EXCEPTION(ConfigInvalidConfigSection, "Invalid config section");

	MAKE_STATIC_EXCEPTION(ParserRunawayComment, "Runaway comment");
	MAKE_STATIC_EXCEPTION(ParserUnknownEntryType, "Unknown EntryType");

	MAKE_STATIC_EXCEPTION(SerializerUnknownOutputType, "Unknown output type");
	MAKE_STATIC_EXCEPTION(SerializerEndDocument, "Unknown output type");
	MAKE_STATIC_EXCEPTION(SerializerRefNotValid, "Unknown output type");

	MAKE_STATIC_EXCEPTION(SorterRefNotValid, "Sorter ref not valid");

	MAKE_DYNAMIC_EXCEPTION(Scalar);
} // namespace TUCSE

#endif // TUCSE_BIB_PARSER_ERROR_H
*/