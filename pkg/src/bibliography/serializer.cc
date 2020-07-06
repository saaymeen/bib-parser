#include "bib-parser/bibliography/reference.h"
#include "bib-parser/bibliography/serializer.h"
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>


using TUCSE::Reference;
using TUCSE::Serializer;


bool Serializer::createHTML(std::vector<Reference> &references, std::string htmlName) {

	for (auto const &reference : references)
	{
		if (!reference.isValid())
		{
			throw new std::exception{};
		}
	}

	std::ofstream file;
	file.open(htmlName + ".html", std::fstream::out);

	for (std::vector<Reference>::size_type i = 0; i != references.size(); i++) {
		std::string citationKey;
		citationKey = references[i].getCitationKey();
		EntryType entryType;
		entryType = references[i].getEntryType();
		std::unordered_map fields = references[i].getFields();

		file << "<h3>" + citationKey + "</h3><br>";
		file << "<h4>" + entryTypeToString[entryType] + "</h4><br>";
		for (const auto &[fieldType, value] : fields) {
			file << fieldTypeToString[fieldType] + ": " + value + "<br>";
		}
		file << "<hr><br>";
	}

	file.close();
	return 0;
}