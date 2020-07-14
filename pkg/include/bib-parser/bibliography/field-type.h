#ifndef TUCSE_BIB_PARSER_FIELD_TYPE_H
#define TUCSE_BIB_PARSER_FIELD_TYPE_H

#include <unordered_map>
#include <string>
#include <cstddef>

namespace TUCSE
{
	enum class FieldType : size_t
	{
		Address = 0x00,
		Annote,
		Author,
		Booktitle,
		Chapter,
		CrossReference,
		Edition,
		Editor,
		HowPublished,
		Institution,
		Journal,
		Key,
		Month,
		Note,
		Number,
		Organization,
		Pages,
		Publisher,
		School,
		Series,
		Title,
		Type,
		Volume,
		Year,

		NumberOf, // NOTE: Must always be the last value in the enum
	};

	extern std::unordered_map<std::string, FieldType> const fieldTypeStrings;
	extern std::unordered_map<FieldType, std::string> const stringsForFieldTypes;

	class FieldTypeHash
	{
		template <typename T>
		std::size_t operator()(T t) const
		{
			return static_cast<std::size_t>(t);
		}
	};
} // namespace TUCSE

#endif // TUCSE_BIB_PARSER_FIELD_TYPE_H