#include <vector>

#include "bib-parser/bibliography/entry-type.h"
#include "bib-parser/bibliography/field-type.h"

namespace TUCSE
{
	std::vector<FieldType> EntryType::getRequiredFieldTypes() const noexcept
	{
		// TODO: dummy
		return {
			FieldType::Address,
		};
	}

	std::vector<FieldType> EntryType::getOptionalFieldTypes() const noexcept
	{
		// TODO: dummy
		return {
			FieldType::Address,
		};
	}

	std::vector<FieldType> EntryType::getIgnoredFieldTypes() const noexcept
	{
		// TODO: dummy
		return {
			FieldType::Address,
		};
	}
} // namespace TUCSE