#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string> //f�r std::string::compare

#include "bib-parser/bibliography/reference.h"
#include "bib-parser/bibliography/sorter.h"

using TUCSE::Reference;
using TUCSE::Sorter;
using Criteria = TUCSE::Sorter::Criteria;
using namespace std;

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

void Sorter::mergeSort_String(std::vector<std::string> &left, std::vector<std::string> &right, std::vector<std::string> &liste)
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
	liste.push_back("ANanas");
	liste.push_back("ga");
	liste.push_back("bb");
	liste.push_back("aa");
	liste.push_back("db");
	liste.push_back("ca");
	liste.push_back("wb");
	liste.push_back("fa");
	liste.push_back("ab");
	liste.push_back("az");
	liste.push_back("a");
	liste.push_back("Z");

	//std::sort(liste.begin(), liste.end(),compareFunction);
	sort_String(liste);

	//Ausgabe der Liste zum Testen des Ergbnisses
	for (auto it = liste.begin(); it != liste.end(); it++)
	{
		std::cout << *it << '\n'
				  << std::endl;
	}
}

void Sorter::sort(std::vector<Reference> &references, Criteria const criteria) noexcept
{
	// FIXME: Implement
	// mithilfe von if-Bedingungen abnfangen, ob String oder Integer Vektor sortiert werden muss (also nach Author, Entry Type oder nach Year)
	// entsprechende Funktionen aufrufen und Vektor sortieren lassen
}