#include "Tools/TextureCompiler.h"

std::shared_ptr<TDS::TextureCompiler> TDS::TextureCompiler::m_Instance{};
void TDS::TextureCompiler::Init()
{
    //std::function<void(std::string, std::string)> convertTexFunc = [this](std::string DescSrc, std::string texOutPath)
    //{
    //    m_CurrDesc.Serialize(DescSrc, true);
    //    std::string filePath = "../assets/textures/";
    //    filePath += m_CurrDesc.m_Descriptor.m_BitMapPath;
    //    DXGI_FORMAT format = ConvertStringToFormat(m_CurrDesc.m_Descriptor.m_Format);
    //    if (!LoadTexture(StringToWstring(filePath)))
    //    {
    //        std::cout << "ERROR : Failed to load bitmap : " << m_CurrDesc.m_Descriptor.m_BitMapPath.c_str() << std::endl;
    //        return;
    //    }
    //    if (!Compress(format))
    //    {
    //        std::cout << "ERROR : Failed to compressed texture : " << m_CurrDesc.m_Descriptor.m_BitMapPath.c_str() << std::endl;

    //    }
    //    if (!SaveCompressedTexture(StringToWstring(texOutPath)))
    //    {
    //        std::cout << "ERROR : Failed to output : " << m_CurrDesc.m_Descriptor.m_BitMapPath.c_str() << " to DDS format" << std::endl;
    //        return;
    //    }

    //};

    //CommandParser::GetInstance()->AddCommand(convertTexFunc, "TextureCompile");
}


void TDS::TextureCompiler::RunCompiler(const std::wstring& in, const std::wstring& out)
{
    Compress(DXGI_FORMAT_BC1_UNORM);
}

bool TDS::TextureCompiler::LoadTexture(const std::wstring& path)
{
    HRESULT hr = DirectX::LoadFromWICFile(path.c_str(), DirectX::WIC_FLAGS_NONE, nullptr, m_Image);

    return SUCCEEDED(hr);
}

bool TDS::TextureCompiler::Compress(DXGI_FORMAT format)
{
    if (m_Image.GetMetadata().width % 4 != 0 || m_Image.GetMetadata().height % 4 != 0)
    {
        std::cout << "dimensions has to be multiples of 4" << std::endl;
        return false;
    }
    HRESULT hr = DirectX::Compress(
        m_Image.GetImages(), m_Image.GetImageCount(),
        m_Image.GetMetadata(), format,
        DirectX::TEX_COMPRESS_DEFAULT, 0.93f,
        m_Out
    );
    return SUCCEEDED(hr);
}

bool TDS::TextureCompiler::SaveCompressedTexture(const std::wstring& outPath)
{
    HRESULT hr = DirectX::SaveToDDSFile(
        m_Image.GetImages(), m_Image.GetImageCount(),
        m_Image.GetMetadata(),
        DirectX::DDS_FLAGS_NONE, outPath.c_str()
    );
    return SUCCEEDED(hr);
}

DXGI_FORMAT TDS::TextureCompiler::ConvertStringToFormat(std::string_view format)
{
    if (format == "R32G32B32A32_FLOAT")
    {
        return DXGI_FORMAT_R32G32B32A32_FLOAT;
    }
    else if (format == "R32G32B32A32_UINT")
    {
        return DXGI_FORMAT_R32G32B32A32_UINT;
    }
    else if (format == "R32G32B32A32_SINT")
    {
        return DXGI_FORMAT_R32G32B32A32_SINT;
    }
    else if (format == "R32G32B32_FLOAT")
    {
        return DXGI_FORMAT_R32G32B32_FLOAT;
    }
    else if (format == "R32G32B32_UINT")
    {
        return DXGI_FORMAT_R32G32B32_UINT;
    }
    else if (format == "R32G32B32_SINT")
    {
        return DXGI_FORMAT_R32G32B32_SINT;
    }
    else if (format == "R16G16B16A16_FLOAT")
    {
        return DXGI_FORMAT_R16G16B16A16_FLOAT;
    }
    else if (format == "R16G16B16A16_UNORM")
    {
        return DXGI_FORMAT_R16G16B16A16_UNORM;
    }
    else if (format == "R16G16B16A16_UINT")
    {
        return DXGI_FORMAT_R16G16B16A16_UINT;
    }
    else if (format == "R16G16B16A16_SNORM")
    {
        return DXGI_FORMAT_R16G16B16A16_SNORM;
    }
    else if (format == "R16G16B16A16_SINT")
    {
        return DXGI_FORMAT_R16G16B16A16_SINT;
    }
    else if (format == "R32G32_FLOAT")
    {
        return DXGI_FORMAT_R32G32_FLOAT;
    }
    else if (format == "R32G32_UINT")
    {
        return DXGI_FORMAT_R32G32_UINT;
    }
    else if (format == "R32G32_SINT")
    {
        return DXGI_FORMAT_R32G32_SINT;
    }
    else if (format == "R10G10B10A2_UNORM")
    {
        return DXGI_FORMAT_R10G10B10A2_UNORM;
    }
    else if (format == "R10G10B10A2_UINT")
    {
        return DXGI_FORMAT_R10G10B10A2_UINT;
    }
    else if (format == "R11G11B10_FLOAT")
    {
        return DXGI_FORMAT_R11G11B10_FLOAT;
    }
    else if (format == "R8G8B8A8_UNORM")
    {
        return DXGI_FORMAT_R8G8B8A8_UNORM;
    }
    else if (format == "R8G8B8A8_UNORM_SRGB")
    {
        return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
    }
    else if (format == "R8G8B8A8_UINT")
    {
        return DXGI_FORMAT_R8G8B8A8_UINT;
    }
    else if (format == "R8G8B8A8_SNORM")
    {
        return DXGI_FORMAT_R8G8B8A8_SNORM;
    }
    else if (format == "R8G8B8A8_SINT")
    {
        return DXGI_FORMAT_R8G8B8A8_SINT;
    }
    else if (format == "R16G16_FLOAT")
    {
        return DXGI_FORMAT_R16G16_FLOAT;
    }
    else if (format == "R16G16_UNORM")
    {
        return DXGI_FORMAT_R16G16_UNORM;
    }
    else if (format == "R16G16_UINT")
    {
        return DXGI_FORMAT_R16G16_UINT;
    }
    else if (format == "R16G16_SNORM")
    {
        return DXGI_FORMAT_R16G16_SNORM;
    }
    else if (format == "R16G16_SINT")
    {
        return DXGI_FORMAT_R16G16_SINT;
    }
    else if (format == "R32_FLOAT")
    {
        return DXGI_FORMAT_R32_FLOAT;
    }
    else if (format == "R32_UINT")
    {
        return DXGI_FORMAT_R32_UINT;
    }
    else if (format == "R32_SINT")
    {
        return DXGI_FORMAT_R32_SINT;
    }
    else if (format == "R8G8_UNORM")
    {
        return DXGI_FORMAT_R8G8_UNORM;
    }
    else if (format == "R8G8_UINT")
    {
        return DXGI_FORMAT_R8G8_UINT;
    }
    else if (format == "R8G8_SNORM")
    {
        return DXGI_FORMAT_R8G8_SNORM;
    }
    else if (format == "R8G8_SINT")
    {
        return DXGI_FORMAT_R8G8_SINT;
    }
    else if (format == "R16_FLOAT")
    {
        return DXGI_FORMAT_R16_FLOAT;
    }
    else if (format == "R16_UNORM")
    {
        return DXGI_FORMAT_R16_UNORM;
    }
    else if (format == "R16_UINT")
    {
        return DXGI_FORMAT_R16_UINT;
    }
    else if (format == "R16_SNORM")
    {
        return DXGI_FORMAT_R16_SNORM;
    }
    else if (format == "R16_SINT")
    {
        return DXGI_FORMAT_R16_SINT;
    }
    else if (format == "R8_UNORM")
    {
        return DXGI_FORMAT_R8_UNORM;
    }
    else if (format == "R8_UINT")
    {
        return DXGI_FORMAT_R8_UINT;
    }
    else if (format == "R8_SNORM")
    {
        return DXGI_FORMAT_R8_SNORM;
    }
    else if (format == "R8_SINT")
    {
        return DXGI_FORMAT_R8_SINT;
    }
    else if (format == "A8_UNORM")
    {
        return DXGI_FORMAT_A8_UNORM;
    }
    else if (format == "R1_UNORM")
    {
        return DXGI_FORMAT_R1_UNORM;
    }
    else if (format == "R9G9B9E5_SHAREDEXP")
    {
        return DXGI_FORMAT_R9G9B9E5_SHAREDEXP;
    }
    else if (format == "R8G8_B8G8_UNORM")
    {
        return DXGI_FORMAT_R8G8_B8G8_UNORM;
    }
    else if (format == "G8R8_G8B8_UNORM")
    {
        return DXGI_FORMAT_G8R8_G8B8_UNORM;
    }
    else if (format == "BC1_UNORM")
    {
        return DXGI_FORMAT_BC1_UNORM;
    }
    else if (format == "BC1_UNORM_SRGB")
    {
        return DXGI_FORMAT_BC1_UNORM_SRGB;
    }
    else if (format == "BC2_UNORM")
    {
        return DXGI_FORMAT_BC2_UNORM;
    }
    else if (format == "BC2_UNORM_SRGB")
    {
        return DXGI_FORMAT_BC2_UNORM_SRGB;
    }
    else if (format == "BC3_UNORM")
    {
        return DXGI_FORMAT_BC3_UNORM;
    }
    else if (format == "BC3_UNORM_SRGB")
    {
        return DXGI_FORMAT_BC3_UNORM_SRGB;
    }
    else if (format == "BC4_UNORM")
    {
        return DXGI_FORMAT_BC4_UNORM;
    }
    else if (format == "BC4_SNORM")
    {
        return DXGI_FORMAT_BC4_SNORM;
    }
    else if (format == "BC5_UNORM")
    {
        return DXGI_FORMAT_BC5_UNORM;
    }
    else if (format == "BC5_SNORM")
    {
        return DXGI_FORMAT_BC5_SNORM;
    }
    else if (format == "B5G6R5_UNORM")
    {
        return DXGI_FORMAT_B5G6R5_UNORM;
    }
    else if (format == "B5G5R5A1_UNORM")
    {
        return DXGI_FORMAT_B5G5R5A1_UNORM;
    }
    else if (format == "B8G8R8A8_UNORM")
    {
        return DXGI_FORMAT_B8G8R8A8_UNORM;
    }
    else if (format == "B8G8R8X8_UNORM")
    {
        return DXGI_FORMAT_B8G8R8X8_UNORM;
    }
    else if (format == "R10G10B10_XR_BIAS_A2_UNORM")
    {
        return DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM;
    }
    else if (format == "B8G8R8A8_UNORM_SRGB")
    {
        return DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
    }
    else if (format == "B8G8R8X8_UNORM_SRGB")
    {
        return DXGI_FORMAT_B8G8R8X8_UNORM_SRGB;
    }
    else if (format == "BC6H_UF16")
    {
        return DXGI_FORMAT_BC6H_UF16;
    }
    else if (format == "BC6H_SF16")
    {
        return DXGI_FORMAT_BC6H_SF16;
    }
    else if (format == "BC7_UNORM")
    {
        return DXGI_FORMAT_BC7_UNORM;
    }
    else if (format == "BC7_UNORM_SRGB")
    {
        return DXGI_FORMAT_BC7_UNORM_SRGB;
    }
    else if (format == "AYUV")
    {
        return DXGI_FORMAT_AYUV;
    }
    else if (format == "Y410")
    {
        return DXGI_FORMAT_Y410;
    }
    else if (format == "Y416")
    {
        return DXGI_FORMAT_Y416;
    }
    else if (format == "NV12")
    {
        return DXGI_FORMAT_NV12;
    }
    else if (format == "P010")
    {
        return DXGI_FORMAT_P010;
    }
    else if (format == "P016")
    {
        return DXGI_FORMAT_P016;
    }
    else if (format == "YUY2")
    {
        return DXGI_FORMAT_YUY2;
    }
    else if (format == "Y210")
    {
        return DXGI_FORMAT_Y210;
    }
    else if (format == "Y216")
    {
        return DXGI_FORMAT_Y216;
    }
    else if (format == "NV11")
    {
        return DXGI_FORMAT_NV11;
    }
    else if (format == "AI44")
    {
        return DXGI_FORMAT_AI44;
    }
    else if (format == "IA44")
    {
        return DXGI_FORMAT_IA44;
    }
    else if (format == "P8")
    {
        return DXGI_FORMAT_P8;
    }
    else if (format == "A8P8")
    {
        return DXGI_FORMAT_A8P8;
    }
    else if (format == "B4G4R4A4_UNORM")
    {
        return DXGI_FORMAT_B4G4R4A4_UNORM;
    }
    else if (format == "P208")
    {
        return DXGI_FORMAT_P208;
    }
    else if (format == "V208")
    {
        return DXGI_FORMAT_V208;
    }
    else if (format == "V408")
    {
        return DXGI_FORMAT_V408;
    }
    else
    {
        return DXGI_FORMAT_UNKNOWN;
    }


}

std::wstring TDS::TextureCompiler::StringToWstring(std::string_view cString)
{
    return std::wstring(cString.begin(), cString.end());
}
