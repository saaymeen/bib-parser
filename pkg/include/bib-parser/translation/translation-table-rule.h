#ifndef TUCSE_BIB_PARSER_TRANSLATION_TABLE_RULE_H
#define TUCSE_BIB_PARSER_TRANSLATION_TABLE_RULE_H

#include "bib-parser/bibliography/field-type.h"
#include "bib-parser/core/serializer-dependencies.h"
#include "bib-parser/core/types.h"

namespace TUCSE
{
	class TranslationTableRule
	{
	public:
		virtual void apply(SerializerDependencies &, std::string const &value) const noexcept = 0;

		TranslationTableRule(FieldType const fieldType, ScalarType const scalarType)
			: fieldType{fieldType}, scalarType{scalarType}
		{
		}

		virtual ~TranslationTableRule() = default;

	protected:
		FieldType const fieldType;
		ScalarType const scalarType;
	};
} // namespace TUCSE

#endif // TUCSE_BIB_PARSER_TRANSLATION_TABLE_RULE_H