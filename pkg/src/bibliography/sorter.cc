#include "bib-parser/bibliography/sorter.h"

namespace TUCSE
{
	std::map<std::string, Sorter::Criteria> const Sorter::argumentMap{
		{"author-asc", Criteria::AuthorAsc},
		{"author-desc", Criteria::AuthorDesc}};
}
