#include <memory>
#include <utility>

#include "bib-parser/translation/translation-table.h"
#include "bib-parser/core/types.h"

using std::move;
using std::shared_ptr;
using TUCSE::TranslationTable;
using FieldType = TUCSE::FieldType;
using TUCSE::TranslationTableRule;
using OutputType = TUCSE::OutputType;
using ScalarType = TUCSE::ScalarType;
using std::map;
using HTMLTag = TUCSE::HTMLTag;
using PDFType = TUCSE::PDFType;
using std::make_pair;
using std::unordered_map;

std::map<std::string, ScalarType> const TranslationTable::scalarTypeStrings{
	{"date", ScalarType::Date},
	{"number", ScalarType::Number},
	{"string", ScalarType::String},
	{"range", ScalarType::Range}};

std::map<std::string, HTMLTag> const TranslationTable::htmlTagStrings{
	{"p", HTMLTag::Paragraph},
	{"h1", HTMLTag::Heading1},
	{"span", HTMLTag::Span},
	{"h2", HTMLTag::Heading2}};

std::map<std::string, PDFType> const TranslationTable::pdfTypeStrings{
	{"text", PDFType::Text},
	{"title", PDFType::Title}};

void TranslationTable::addRule(OutputType const outputType, FieldType const fieldType, shared_ptr<TranslationTableRule> rule) noexcept
{
	if (rules.count(outputType) == 0)
	{
		unordered_map<FieldType, shared_ptr<TranslationTableRule>> emptyRuleList{};
		rules.insert(make_pair(outputType, emptyRuleList));
	}

	rules.at(outputType).insert(make_pair(fieldType, rule));
}

void TranslationTable::addScalarFieldType(FieldType fieldType, ScalarType scalarType) noexcept
{
	scalarFieldTypes.insert(make_pair(fieldType, scalarType));
}

ScalarType TranslationTable::getScalarType(FieldType const fieldType) const
{
	return scalarFieldTypes.at(fieldType);
}

shared_ptr<TranslationTableRule> TranslationTable::getRule(OutputType const outputType, FieldType const fieldType) const
{
	return rules.at(outputType).at(fieldType);
}