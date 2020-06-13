#include <vector>

#include "bib-parser/bibliography/entry-type.h"
#include "bib-parser/bibliography/field-type.h"

namespace TUCSE
{
	std::vector<FieldType> getRequiredFieldTypes(EntryType const entryType) noexcept
	{
		// TODO: dummy
		return {
			FieldType::Address,
		};
	}

	std::vector<FieldType> getOptionalFieldTypes(EntryType const entryType) noexcept
	{
		// TODO: dummy
		return {
			FieldType::Address,
		};
	}

	std::vector<FieldType> getIgnoredFieldTypes(EntryType const entryType) noexcept
	{
		// TODO: dummy
		return {
			FieldType::Address,
		};
	}
} // namespace TUCSE