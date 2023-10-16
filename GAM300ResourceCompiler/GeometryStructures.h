/*!*****************************************************************************
 * \file          GeometryStructures.h
 * \author        Eugene Ho Shu Sheng
 * \par DP email: shushengeugene.ho@digipen.edu
 * \par Course:   CSD3400
 * \par Section:  A
 * \date          01/10/2023
 * \brief         Structure for Geometry
 *******************************************************************************/
#pragma once
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "TDSMath.h"
#include "pch.h"

namespace TDS
{
	/*!*************************************************************************
	 * iColor struct that create a color, either in RGBA or value
	 ***************************************************************************/
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
                new (&m_RGBA) Vec4(color); // Placement new to construct Vec4
                isVec4 = true;
            }
            updateValueFromRGBA();
            return *this;
        }

        iColor& operator = (const uint32_t& color) {
            if (isVec4) {
                m_RGBA.~Vec4(); // Call destructor if currently holding a Vec4
                isVec4 = false;
            }
            m_Value = color;
            updateRGBAFromValue();
            return *this;
        }

        ~iColor() {
            if (isVec4) {
                m_RGBA.~Vec4(); // Call destructor if holding a Vec4
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
    /*!*************************************************************************
	 * RawVertex struct that create a vertex
     ***************************************************************************/
    struct RawVertex
    {
        Vec3 m_Pos;
        Vec2 m_UV;
        Vec4 m_fNormal;
        Vec3 m_fTanget;
        Vec3 m_fBitangent;
        iColor m_Tangent;
        iColor m_Bitangent;
        iColor m_Normal;
        iColor m_Color;
    };

    /*!*************************************************************************
	 * For geom compiler, compile all the geometry into a single file
     ***************************************************************************/
    struct GeomCompiled
    {
        struct Mesh
        {
            std::array<char, 64> m_Name;
        };

        struct SubMesh
        {
            std::uint32_t m_nFaces;
            std::uint32_t m_iIndices;
            std::uint32_t m_iVertices;
            std::uint32_t m_nVertices;
            std::uint16_t m_iMaterial;
        };

        struct ExtraVertices
        {
            Vec2 m_UV;
            Vec3 m_Normal;
            Vec3 m_Tanget;
            Vec3 m_Bitangent;
            std::uint32_t m_Colour;
        };
        std::vector<Mesh> m_Mesh;
        std::vector<SubMesh> m_SubMesh;
        std::vector<Vec3> m_Pos;
        std::vector<ExtraVertices> m_Extra;
        std::vector<std::uint32_t> m_Indices;
    };


    /*!*************************************************************************
	 * Output the geometry into a file from the compiled geometry
     ***************************************************************************/
    struct FinalGeom
    {
        struct SubMesh
        {
            std::vector<Vec3> m_Pos;
            std::vector<GeomCompiled::ExtraVertices> m_Extra;
            std::vector<std::uint32_t> m_Indices;
            std::int32_t m_iMaterial;
        };

        struct Mesh
        {
            std::string m_Name;
            std::vector<SubMesh> m_SubMeshes;
        };

        std::string m_Filename;
        std::vector<Mesh> m_Meshes;

    };

}