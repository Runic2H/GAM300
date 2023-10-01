/*!*****************************************************************************
 * \file          GUID.h
 * \author        Eugene Ho Shu Sheng
 * \par DP email: shushengeugene.ho@digipen.edu
 * \par Course:   CSD3400
 * \par Section:  A
 * \date          01/10/2023
 * \brief         This file contains the declaration of the GUID class.
 *******************************************************************************/
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
        /*!*************************************************************************
		 * Constructor & Destructor for UniqueID class
         ***************************************************************************/
        UniqueID() noexcept;
        UniqueID(std::uint64_t value) noexcept;
		/*!*************************************************************************
		 * Resetting and Creating UniqueID
		 ***************************************************************************/
        void reset() noexcept;
        static UniqueID CreateUniqueGuid() noexcept;

        /*!*************************************************************************
         * Helper Functions
         ***************************************************************************/
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