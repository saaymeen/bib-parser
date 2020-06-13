#include <vector>

#include "bib-parser/bibliography/reference.h"
#include "bib-parser/bibliography/sorter.h"

using TUCSE::Reference;
using TUCSE::Sorter;
using Criteria = TUCSE::Sorter::Criteria;

std::map<std::string, Sorter::Criteria> const TUCSE::Sorter::argumentMap{
	{"author-asc", Criteria::AuthorAsc},
	{"author-desc", Criteria::AuthorDesc}};

void Sorter::sort(std::vector<Reference> &references, Criteria const criteria) noexcept
{
	// FIXME: Implement
}