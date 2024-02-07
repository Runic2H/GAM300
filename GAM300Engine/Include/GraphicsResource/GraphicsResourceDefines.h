#pragma once
#include "MathCommon.h"
namespace TDS
{










    //OLD
    struct iColor {
        union {
            Vec4       m_RGBA;
            uint32_t   m_Value;
        };
        bool isVec4;

        iColor()
            : m_Value(0x00000000), isVec4(false)
        {}

        iColor(const Vec4& color)
            : m_RGBA(color), isVec4(true)
        {
            updateValueFromRGBA();
        }

        iColor(uint32_t color)
            : m_Value(color), isVec4(false)
        {
            updateRGBAFromValue();
        }

        iColor(const iColor& other)
            : isVec4(other.isVec4)
        {
            if (isVec4) {
                new (&m_RGBA) Vec4(other.m_RGBA);
            }
            else {
                m_Value = other.m_Value;
            }
        }

        iColor& operator=(const iColor& other) {
            if (this == &other) return *this;

            if (isVec4) {
                m_RGBA.~Vec4();
            }

            isVec4 = other.isVec4;
            if (isVec4) {
                new (&m_RGBA) Vec4(other.m_RGBA);
            }
            else {
                m_Value = other.m_Value;
            }

            return *this;
        }

        iColor& operator = (const Vec4& color) {
            if (isVec4) {
                m_RGBA = color;
            }
            else {
                new (&m_RGBA) Vec4(color);
                isVec4 = true;
            }
            updateValueFromRGBA();
            return *this;
        }

        iColor& operator = (const uint32_t& color) {
            if (isVec4) {
                m_RGBA.~Vec4();
                isVec4 = false;
            }
            m_Value = color;
            updateRGBAFromValue();
            return *this;
        }

        ~iColor() {
            if (isVec4) {
                m_RGBA.~Vec4();
            }
        }

    private:
        void updateValueFromRGBA() {
            m_Value = 0;
            m_Value |= static_cast<int>(m_RGBA.x * 255.0f) << 24;
            m_Value |= static_cast<int>(m_RGBA.y * 255.0f) << 16;
            m_Value |= static_cast<int>(m_RGBA.z * 255.0f) << 8;
            m_Value |= static_cast<int>(m_RGBA.w * 255.0f);
        }

        void updateRGBAFromValue() {
            m_RGBA.x = static_cast<float>((m_Value >> 24) & 0xFF) / 255.0f;
            m_RGBA.y = static_cast<float>((m_Value >> 16) & 0xFF) / 255.0f;
            m_RGBA.z = static_cast<float>((m_Value >> 8) & 0xFF) / 255.0f;
            m_RGBA.w = static_cast<float>(m_Value & 0xFF) / 255.0f;
        }
    };
}