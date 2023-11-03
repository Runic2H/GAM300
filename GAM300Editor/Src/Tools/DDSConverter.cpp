#include "Tools/DDSConverter.h"
#include "Logger/Logger.h"
#include "Tools/FileExtensions.h"

std::wstring TDS::DDSConverter::StringToWstring(std::string_view cString)
{
    return std::wstring(cString.begin(), cString.end());
}

void TDS::DDSConverter::Init()
{
    HRESULT hr{};
    hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    if (FAILED(hr))
    {
        TDS_ERROR("Failed to initialize COM library.");

        return;
    }
}

void TDS::DDSConverter::ConvertToDDS(std::string_view path, std::string_view outPath, DXGI_FORMAT ddsFormat)
{
    HRESULT hr{};
    DirectX::ScratchImage m_Image{};
    std::wstring InWPath = StringToWstring(path.data());
    hr = DirectX::LoadFromWICFile(InWPath.c_str(), DirectX::WIC_FLAGS_NONE, nullptr, m_Image);
    if (FAILED(hr)) {
        TDS_ERROR("Failed to load {}", path);
        return;
    }

    if (ddsFormat == DXGI_FORMAT_UNKNOWN)
    {
        const DirectX::TexMetadata& metadata = m_Image.GetMetadata();
        ddsFormat = metadata.format;
    }

    DirectX::ScratchImage ddsImage;
    hr = DirectX::Compress(
        m_Image.GetImages(), m_Image.GetImageCount(),
        m_Image.GetMetadata(), ddsFormat,
        DirectX::TEX_COMPRESS_DEFAULT, 0.93f,
        ddsImage
    );
    if (FAILED(hr)) {
        TDS_ERROR("Failed to convert image format");
        return;
    }

    std::wstring OutWPath = StringToWstring(outPath);
    hr = DirectX::SaveToDDSFile(
        ddsImage.GetImages(), ddsImage.GetImageCount(),
        ddsImage.GetMetadata(),
        DirectX::DDS_FLAGS_NONE, OutWPath.c_str());
    if (FAILED(hr)) {
        TDS_ERROR("Failed to save DDS file");
        return;
    }
}


void TDS::DDSConverter::Destroy()
{
    CoUninitialize();
}
