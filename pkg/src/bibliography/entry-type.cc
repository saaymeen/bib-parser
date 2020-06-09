#include <vector>

#include "bib-parser/bibliography/entry-type.h"
#include "bib-parser/bibliography/field-type.h"

namespace TUCSE
{
	std::vector<FieldType> EntryType::getRequiredFieldTypes() const noexcept
	{
		return {
			FieldType::Address,
		};
		switch (value)
		{
		case EntryType::Article:
			return {
				FieldType::Address,
			};
		}
	}

	std::vector<FieldType> EntryType::getOptionalFieldTypes() const noexcept
	{
		return {
			FieldType::Address,
		};
	}

	std::vector<FieldType> EntryType::getIgnoredFieldTypes() const noexcept
	{
		return {
			FieldType::Address,
		};
	}
} // namespace TUCSE