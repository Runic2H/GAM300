#include "Serialization/BinarySerialize/BinarySerializer.h"


namespace TDS
{
	BinarySerializer::BinarySerializer()
	{
	}
	BinarySerializer::~BinarySerializer()
	{
	}
	bool BinarySerializer::OpenFile(std::string_view path, bool is_read)
	{
		if (is_read)
			fileStream.open(path.data(), std::ios::in | std::ios::binary);

		else
			fileStream.open(path.data(), std::ios::out | std::ios::binary);

		if (!fileStream.is_open())
			return false;

		return true;
	}
	void BinarySerializer::Close()
	{
		if (fileStream.is_open())
			fileStream.close();
	}
}