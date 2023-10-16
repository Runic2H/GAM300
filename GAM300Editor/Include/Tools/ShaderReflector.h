#pragma once
#include "Shader/ShaderData.h"
namespace TDS
{
	class ShaderReflector
	{
	public:
		inline static std::shared_ptr<ShaderReflector> m_Instance;
		ShaderMetaData m_Output;
		inline static std::shared_ptr<ShaderReflector> GetInstance()
		{
			if (m_Instance == 0)
				m_Instance = std::make_shared<ShaderReflector>();
			return m_Instance;
		}
		void Init(std::string_view srcFolder, std::string_view OutFolder);
		void StartReflectingAll(std::string_view Path);
		void LoadSPIRVBinaries(const std::string_view fileName, std::vector<std::uint32_t>& spirv);
		void ReflectUniform(const std::vector<std::uint32_t>& spirvData, const std::string_view fileName);
		void ReflectSSBO(const std::vector<std::uint32_t>& spirvData, const std::string_view fileName);
		void ReflectPushConstants(const std::vector<std::uint32_t>& spirvData, const std::string_view fileName);
		void ReflectSampler(const std::vector<std::uint32_t>& spirvData, const std::string_view fileName);
		void ReflectStorageImages(const std::vector<std::uint32_t>& spirvData, const std::string_view fileName);
		void Serialize(std::string_view Output);

		void CleanUp();

	};
}