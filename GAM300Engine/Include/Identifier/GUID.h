#pragma once
#include <random>
#include <cstdarg>
#include <utility>
#include <sstream>
#include <iomanip>

namespace TDS
{
    class UniqueID
    {
    public:

        UniqueID() noexcept;
        UniqueID(std::uint64_t value) noexcept;
        void reset() noexcept;
        static UniqueID CreateUniqueGuid() noexcept;

        bool operator==(const UniqueID& other) const noexcept
        {
            return m_value == other.m_value;
        }

        bool operator!=(const UniqueID& other) const noexcept
        {
            return m_value != other.m_value;
        }
        UniqueID& operator=(const UniqueID& other) noexcept
        {
            m_value = other.m_value;
            return *this;
        }

        UniqueID& operator=(const std::uint64_t& other) noexcept
        {
            m_value = other;
            return *this;
        }


        inline bool isValid() const noexcept
        {
            return m_value != 0;
        }

        inline bool isNull() const noexcept
        {
            return m_value == 0;
        }

        inline void setNull() noexcept
        {
            m_value = 0;
        }
        std::string getStringHex() const noexcept;
        inline const std::uint64_t GetUniqueID()
        {
            return m_value;
        }


    private:
        std::uint64_t m_value;
    };
}