#ifndef TUCSE_BIB_PARSER_REFERENCE_H
#define TUCSE_BIB_PARSER_REFERENCE_H

#include <string>
#include <unordered_map>

#include "entry-type.h"
#include "field-type.h"

namespace TUCSE
{
	class Reference
	{
	public:
		Reference(std::string const &citationKey, EntryType const entryType);

		void addField(FieldType const fieldType, std::string const &value) noexcept;

		bool isValid() const noexcept;
		std::string getCitationKey() const noexcept;
		EntryType getEntryType() const noexcept;
		std::unordered_map<FieldType, std::string> getFields() const noexcept;

		std::string getFieldValue(FieldType const fieldType) const;

	private:
		std::string citationKey;
		EntryType entryType;
		std::unordered_map<FieldType, std::string> fields;
	};
} // namespace TUCSE

#endif // TUCSE_BIB_PARSER_REFERENCE_H