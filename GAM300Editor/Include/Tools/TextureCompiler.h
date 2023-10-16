#pragma once
#include "pch.h"
#include "DirectXTex.h"
#include "CompilerSettings.h"
namespace TDS
{
	class TextureCompiler
	{
	public:
		static std::shared_ptr<TextureCompiler> m_Instance;
		TextureCompiler() = default;
		~TextureCompiler() = default;
		void Init();
		void RunCompiler(const std::wstring& in, const std::wstring& out);
		bool LoadTexture(const std::wstring& path);
		bool Compress(DXGI_FORMAT format);
		bool SaveCompressedTexture(const std::wstring& outPath);
		DXGI_FORMAT ConvertStringToFormat(std::string_view format);
		std::wstring StringToWstring(std::string_view cString);

		inline static std::shared_ptr<TextureCompiler> GetInstance()
		{
			if (m_Instance == 0)
				m_Instance = std::make_shared<TextureCompiler>();
			return m_Instance;
		}

	private:
		TextureDescriptor m_CurrDesc;
		DirectX::ScratchImage m_Image;
		DirectX::ScratchImage m_Out;
	};
}