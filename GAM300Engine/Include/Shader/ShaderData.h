#pragma once
#include "pch.h"
namespace TDS
{
	enum class VAR_TYPE
	{
		None = 0,

		Float,
		VEC2,
		VEC3,
		VEC4,

		MAT3,
		MAT4,

		BOOL,
		BYTE
	};

	enum class SHADER_FLAG : std::int32_t
	{
		NONE = 0,
		VERTEX = 1,
		FRAGMENT = 2,
		COMPUTE = 4
	};

	enum class BUFFER_TYPE
	{
		UNIFORM,
		SSBO,
		SAMPLER,
		STORAGE_IMAGE,
	};


	struct BufferVariable
	{
		size_t m_Size = 0;
		size_t m_Offset = 0;
		std::string m_Name = "";
		VAR_TYPE m_Var;
	};


	struct PushContantReflect
	{
		uint32_t m_Offset = 0;
		uint32_t m_Size = 0;
	};

	struct Uniform
	{
		BUFFER_TYPE m_BufferType;
		std::uint32_t m_BindingPoint = 0;
		std::string m_InstanceName = "";
		size_t m_Size = 0;
		std::vector<BufferVariable> m_UniformsBuffer;
	};



	struct SamplerBuffer
	{
		std::uint32_t m_Location = 0;
		std::uint32_t m_BindingPoint = 0;
		std::uint32_t m_Dimension = 0;
		std::uint32_t m_ArraySize = 0;
		std::string   m_Name;
		BUFFER_TYPE   m_BufferType;
	};

	struct ReflectionData
	{
		PushContantReflect m_PushConstant{};
		//If the names appear twice.
		std::map<std::string, SamplerBuffer> m_ImageSamplers;
		std::map<std::string, SamplerBuffer> m_StorageImages;
		std::map<std::string, Uniform>		m_UniformBuffers;

		void Reset()
		{
			m_PushConstant = {};
			m_ImageSamplers.clear();
			m_StorageImages.clear();
			m_UniformBuffers.clear();

		}
	};

	struct ShaderData
	{
		SHADER_FLAG m_StageType;
		std::string m_ShaderName;
		ReflectionData m_ReflectedData;
	};

	struct ShaderMetaData
	{
		std::unordered_map<std::string, ShaderData> m_ShaderDatas;
	};


}