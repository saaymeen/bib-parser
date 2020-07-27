#ifndef TUCSE_BIB_PARSER_TRANSLATION_TABLE_RULE_H
#define TUCSE_BIB_PARSER_TRANSLATION_TABLE_RULE_H

#include "bib-parser/bibliography/field-type.h"
#include "bib-parser/core/serializer-dependencies.h"
#include "bib-parser/core/types.h"

namespace TUCSE
{
	// TranslationTableRules stores information about how to translate the value of a given field type into the specified output format.
	class TranslationTableRule
	{
	public:
		// apply writes the given value into the output file taken from the dependencies, taking the rule specification into account.
		virtual void apply(SerializerDependencies &, std::string const &value) const noexcept = 0;

		// TranslationTableRule default constructor.
		TranslationTableRule(FieldType const fieldType, ScalarType const scalarType)
			: fieldType{fieldType}, scalarType{scalarType}
		{
		}

		// ~TranslationTableRule default destructor
		virtual ~TranslationTableRule() = default;

	protected:
		FieldType const fieldType;
		ScalarType const scalarType;
	};
} // namespace TUCSE

#endif // TUCSE_BIB_PARSER_TRANSLATION_TABLE_RULE_H