#include "bib-parser/bibliography/reference.h"

namespace TUCSE
{
	Reference::Reference(std::string const &citationKey, EntryType const entryType)
		: citationKey{citationKey}, entryType{entryType}, fields{} {};

	EntryType Reference::getEntryType() const noexcept
	{
		return entryType;
	}
} // namespace TUCSE