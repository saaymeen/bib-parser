#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <stdexcept>

#include "bib-parser/bibliography/reference.h"
#include "bib-parser/core/sorter.h"
#include "bib-parser/core/util.h"
#include "bib-parser/bibliography/field-type.h"

using TUCSE::Reference;
using TUCSE::Sorter;
using Criteria = TUCSE::Sorter::Criteria;
using namespace std;
using TUCSE::stringToLowercase;
using FieldType = TUCSE::FieldType;

void Sorter::setCriteria(Criteria const criteria) noexcept
{
	this->criteria = criteria;
}

void Sorter::apply(std::vector<Reference> &references) const
{
	if (criteria == Criteria::NoSort)
	{
		return;
	}

	for (auto const &reference : references)
	{
		if (!reference.isValid())
		{
			throw new std::exception{};
		}
	}

	sort(references.begin(), references.end(), [this](Reference const &left, Reference const &right) {
		switch (criteria)
		{
		case Criteria::AuthorAsc:
			return compareAuthor(left, right);
		case Criteria::AuthorDesc:
			return !compareAuthor(left, right);
		}
		return false;
	});

	// FIXME: Implement
	// mithilfe von if-Bedingungen abnfangen, ob String oder Integer Vektor sortiert werden muss (also nach Author, Entry Type oder nach Year)
	// entsprechende Funktionen aufrufen und Vektor sortieren lassen
}

// Return true if left's author it greater than right's author
bool Sorter::compareAuthor(Reference const &left, Reference const &right) noexcept
{
	string leftValue;
	string rightValue;

	try
	{
		leftValue = left.getFieldValue(FieldType::Author);
	}
	catch (std::out_of_range const &exception)
	{
		return false;
	}

	try
	{
		rightValue = right.getFieldValue(FieldType::Author);
	}
	catch (std::out_of_range const &exception)
	{
		return true;
	}

	return leftValue < rightValue;
}

std::map<std::string, Sorter::Criteria> const TUCSE::Sorter::argumentMap{
	{"author-asc", Criteria::AuthorAsc},
	{"author-desc", Criteria::AuthorDesc},
	{"key-asc", Criteria::CitationKeyAsc},
	{"key-desc", Criteria::CitationKeyDesc},
	{"type-asc", Criteria::EntryTypeAsc},
	{"type-desc", Criteria::EntryTypeDesc}};

void Sorter::mergeSort_Integer(std::vector<int> &left, std::vector<int> &right, std::vector<int> &liste)
{
	int nL = left.size();
	int nR = right.size();

	int i = 0;
	int j = 0;
	int k = 0;

	while (j < nL && k < nR)
	{
		if (left[j] < right[k])
		{
			liste[i] = left[j];
			j++;
		}
		else
		{
			liste[i] = right[k];
			k++;
		}
		i++;
	}
	while (j < nL)
	{
		liste[i] = left[j];
		j++;
		i++;
	}

	while (k < nR)
	{
		liste[i] = right[k];
		k++;
		i++;
	}
}

void Sorter::sort_Integer(std::vector<int> &liste)
{
	//mergeSort zum Sortieren eines Vectors mit Integer-Elementen
	if (liste.size() <= 1)
		return;

	int mid = liste.size() / 2;
	std::vector<int> left;
	std::vector<int> right;
	for (size_t j = 0; j < mid; j++)
	{
		left.push_back(liste[j]);
	}
	for (size_t j = 0; j < (liste.size()) - mid; j++)
	{
		right.push_back(liste[mid + j]);
	}

	sort_Integer(left);
	sort_Integer(right);
	mergeSort_Integer(left, right, liste);
}

void Sorter::test_Integer()
{
	//std::vector<int> liste = createListe();
	std::vector<int> liste;
	liste.push_back(int(4));
	liste.push_back(int(2));
	liste.push_back(int(3));
	liste.push_back(int(1));
	liste.push_back(int(6));
	liste.push_back(int(9));
	liste.push_back(int(7));
	liste.push_back(int(8));

	sort_Integer(liste);

	for (auto it = liste.begin(); it != liste.end(); it++)
	{
		std::cout << *it << std::endl;
	}
}

void Sorter::changeToLower(std::string &str)
{
	for (auto &c : str)
	{
		c = tolower(c);
	}
}

void Sorter::mergeSort_String(std::vector<std::string> &left, std::vector<std::string> &right, std::vector<std::string> &liste)
{
	int nL = left.size();
	int nR = right.size();

	int i = 0;
	int j = 0;
	int k = 0;
	std::string tmp_left;
	std::string tmp_right;

	while (j < nL && k < nR)
	{
		//kopiere den String und wandle alles in Kleinbuchstaben um
		tmp_left = left[j];
		tmp_right = right[k];

		changeToLower(tmp_left);
		changeToLower(tmp_right);

		if (tmp_left < tmp_right)
		{
			liste[i] = left[j];
			j++;
		}
		else
		{
			liste[i] = right[k];
			k++;
		}
		i++;
	}

	while (j < nL)
	{
		liste[i] = left[j];
		j++;
		i++;
	}

	while (k < nR)
	{
		liste[i] = right[k];
		k++;
		i++;
	}
}

void Sorter::sort_String(std::vector<std::string> &liste)
{
	//mergeSort zum Sortieren eines Vectors mit Integer-Elementen
	if (liste.size() <= 1)
		return;

	int mid = liste.size() / 2;
	std::vector<std::string> left;
	std::vector<std::string> right;
	for (size_t j = 0; j < mid; j++)
	{
		left.push_back(liste[j]);
	}
	for (size_t j = 0; j < (liste.size()) - mid; j++)
	{
		right.push_back(liste[mid + j]);
	}

	sort_String(left);
	sort_String(right);
	mergeSort_String(left, right, liste);
}

void Sorter::test_String()
{
	std::vector<std::string> liste;
	liste.push_back("Hello World");
	liste.push_back("Hello Student");
	liste.push_back("Ananas");
	liste.push_back("ga");
	liste.push_back("ab");
	liste.push_back("aa");
	liste.push_back("db");
	liste.push_back("ca");
	liste.push_back("wb");
	liste.push_back("fa");
	liste.push_back("ab");
	liste.push_back("az");
	liste.push_back("a");
	liste.push_back("z");

	//std::sort(liste.begin(), liste.end(),compareFunction);
	sort_String(liste);

	//Ausgabe der Liste zum Testen des Ergbnisses
	for (auto it = liste.begin(); it != liste.end(); it++)
	{
		std::cout << *it << '\n'
				  << std::endl;
	}
}
