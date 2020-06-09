#ifndef TUCSE_BIB_PARSER_ENTRY_TYPE_H
#define TUCSE_BIB_PARSER_ENTRY_TYPE_H

#include <cstdint>
#include <vector>

#include "field-type.h"

namespace TUCSE
{
	class EntryType
	{
	public:
		enum Value : uint8_t
		{
			Article = 0x00,
			Book,
			Booklet,
			Conference,
			InBook,
			InCollection,
			InProceedings,
			Manual,
			MastersThesis,
			Miscellaneous,
			PHDThesis,
			Proceedings,
			TechReport,
			Unpublished,

			NumberOf, // Must always be the last value in the enum
		};

		EntryType() = default;
		constexpr EntryType(Value type) : value{type} {}

		operator Value() const
		{
			return value;
		}

		explicit operator bool() = delete;

		std::vector<FieldType> getOptionalFieldTypes() const noexcept;
		std::vector<FieldType> getRequiredFieldTypes() const noexcept;
		std::vector<FieldType> getIgnoredFieldTypes() const noexcept;

	private:
		Value const value;
	};
} // namespace TUCSE

#endif // TUCSE_BIB_PARSER_ENTRY_TYPE_H
