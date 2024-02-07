#pragma once
#include "Compressonator/cmp_compressonatorlib/compressonator.h"
namespace TDS
{
	struct TextureCompilerSetting
	{
		struct Desc
		{
			std::string m_EncoderString = "CPU";
			std::string m_FormatString = "BC7";
			std::uint32_t Width = 0.f, height = 0.f;
			float		m_FloatQuality = 1.f;
		};
		Desc m_Desc;
		bool SerializeSettings(std::string_view FilePath, bool Read);

	};
	class TextureCompressor
	{
	public:
		TextureCompressor();
		~TextureCompressor();
		CMP_Compute_type		GetComputeType(std::string_view computeType);
		CMP_FORMAT				GetCompressorFormat(std::string_view setting);
		void					Run(std::string_view path, std::string_view out);
		bool					LoadTexture(std::string_view path);
		void					SetCompressionSetting(TextureCompilerSetting setting);

		static inline TextureCompressor&
			GetInstance()
		{
			if (m_Instance == nullptr)
				m_Instance = std::make_shared<TextureCompressor>();
			return *m_Instance;

		}
		inline void ToggleCompression(bool condition)
		{
			m_ToggleCompression = condition;
		}
	private:
		bool m_ToggleCompression = true;
		CMP_MipSet m_Input;
		CMP_MipSet m_Output;
		KernelOptions m_Options;
		inline static std::shared_ptr<TextureCompressor> m_Instance = nullptr;
	};
}