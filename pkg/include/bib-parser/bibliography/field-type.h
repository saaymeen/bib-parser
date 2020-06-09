#ifndef TUCSE_BIB_PARSER_FIELD_TYPE_H
#define TUCSE_BIB_PARSER_FIELD_TYPE_H

#include <cstdint>

namespace TUCSE
{
	class FieldType
	{
	public:
		enum Value : uint8_t
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

			NumberOf, // Must always be the last value in the enum
		};

		FieldType() = default;
		constexpr FieldType(Value type) : value{type} {}

		operator Value() const
		{
			return value;
		}

		explicit operator bool() = delete;

	private:
		Value const value;
	};

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