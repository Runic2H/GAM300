#include "Tools/FileExtensions.h"

namespace TDS
{
	std::string RemoveFileExtension(std::string_view path, std::string_view extension)
	{

		std::string result(path);
		size_t pos = result.rfind(extension);

		if (pos != std::string::npos && pos + extension.size() == result.size())
			result.erase(pos);


		return result;

	}

}