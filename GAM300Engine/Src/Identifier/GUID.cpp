#include "Identifier/GUID.h"

namespace TDS
{
    UniqueID::UniqueID() noexcept : m_value(0)
    {
    }
    UniqueID::UniqueID(std::uint64_t value) noexcept :m_value(value)
    {
    }
    UniqueID UniqueID::CreateUniqueGuid() noexcept
    {
        static std::random_device rd;
        static std::mt19937_64 gen(rd());
        std::uniform_int_distribution<std::uint64_t> dis;
        std::uint64_t id = dis(gen) | 1ull;
        return UniqueID(id);
    }

    std::string UniqueID::getStringHex() const noexcept
    {
        std::stringstream ss{};
        ss << std::hex << std::setw(16) << std::setfill('0') << m_value;
        return ss.str();
    }
    void UniqueID::reset() noexcept
    {
        m_value = CreateUniqueGuid().m_value;
    }
}