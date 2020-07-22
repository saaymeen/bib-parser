#ifndef TUCSE_BIB_PARSER_SERIALIZER_DEPENDENCIES_H
#define TUCSE_BIB_PARSER_SERIALIZER_DEPENDENCIES_H

#include <fstream>
#include <memory>

namespace TUCSE
{
	class SerializerDependencies
	{
	public:
		SerializerDependencies(std::shared_ptr<std::ofstream> outputFile)
			: outputFile{outputFile}
		{
		}

		std::shared_ptr<std::ofstream> outputFile;
	};
} // namespace TUCSE

#endif // TUCSE_BIB_PARSER_SERIALIZER_DEPENDENCIES_H