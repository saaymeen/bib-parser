#include "bib-parser/core/translation-table.h"
#include "bib-parser/core/types.h"
#include <memory>

using std::move;
using std::unique_ptr;
using TUCSE::TranslationTable;
using FieldType = TUCSE::FieldType;
using TUCSE::TranslationTableRule;
using OutputType = TUCSE::OutputType;
using ScalarType = TUCSE::ScalarType;
using std::map;
using HTMLTag = TUCSE::HTMLTag;
using PDFType = TUCSE::PDFType;

std::map<std::string, ScalarType> const TranslationTable::scalarTypeStrings{
	{"date", ScalarType::Date},
	{"number", ScalarType::Number},
	{"string", ScalarType::String}};

std::map<std::string, HTMLTag> const TranslationTable::htmlTagStrings{
	{"p", HTMLTag::Paragraph},
	{"h1", HTMLTag::Heading1}};

std::map<std::string, PDFType> const TranslationTable::pdfTypeStrings{
	{"text", PDFType::Text},
	{"title", PDFType::Title}};

void TranslationTable::addRule(OutputType outputType, FieldType fieldType, unique_ptr<TranslationTableRule> rule) noexcept
{
}

void TranslationTable::addScalarFieldType(FieldType fieldType, ScalarType scalarType) noexcept
{
}