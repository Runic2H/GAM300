#ifndef VECTOR4_H
#define VECTOR4_H

#include "MathCommon.h"

namespace TDS
{
class Vec2;
class Vec3;
class Vec4
{
public:
    // Constructors and destructors
    Vec4();
    Vec4(const Vec4& v); // Copy constructor
    Vec4(float value); // Constructor with one value
    Vec4(float data[]); // Constructor with array of values
    Vec4(float newX, float newY, float newZ, float newW); // Constructor with four values
    Vec4(const Vec2& v, float newZ, float newW); // Constructor with Vec2 and two values
    Vec4(const Vec3& v, float newW); // Constructor with Vec4 and one value
    Vec4(const float* newX, const float* newY, const float* newZ, const float* newW); // Constructor with four pointers
    //~Vec4();

    // Static Properties
    DLL_API static Vec4 one();
    DLL_API static Vec4 zero();
    DLL_API static Vec4 positiveInfinity();
    DLL_API static Vec4 negativeInfinity();

    // Properties
    DLL_API float magnitude();
    Vec4 normalize();
    DLL_API float sqrMagnitude();

    // Public Methods
    DLL_API bool Equals(const Vec4& v);
    inline DLL_API void Normalize();
    DLL_API void Set(float newX, float newY, float newZ, float newW);
    std::string ToString();

    // Static Methods
    // Returns the distance between a and b.
    static float Distance(Vec4 a, Vec4 b);
    // Dot Product of two vectors.
    static float Dot(const Vec4 lhs, const Vec4 rhs);
    // Linearly interpolates between two vectors.
    static Vec4 Lerp(const Vec4 a, const Vec4 b, float t);
    // Linearly interpolates between two without clamping the interpolant.
    static Vec4 LerpUnclamped(const Vec4 a, const Vec4 b, float t);
    // Returns a vector that is made from the largest components of two vectors.
    static Vec4 Max(const Vec4 lhs, const Vec4 rhs);
    // Returns a vector that is made from the smallest components of two vectors.
    static Vec4 Min(const Vec4 lhs, const Vec4 rhs);
    // Moves a point current in a straight line towards a target point.
    static Vec4 MoveTowards(Vec4 current, Vec4 target, float maxDistanceDelta);
    // Makes this vector have a magnitude of 1.
    static Vec4 Normalize(Vec4 value);
    // Projects a vector onto another vector.
    static Vec4 Project(Vec4 vector, Vec4 onNormal);
    // Multiplies two vectors component-wise.
    static Vec4 Scale(Vec4 a, Vec4 b);
    // Multiplies every component of this vector by the same component of scale.
    void Scale(Vec4 scale);

    // Operators
    Vec4& operator=(const Vec4& v);
    Vec4& operator+=(float scalar);
    Vec4& operator+=(const Vec4& v);
    Vec4& operator-=(float scalar);
    Vec4& operator-=(const Vec4& v);
    Vec4& operator*=(float scalar);
    Vec4& operator*=(const Vec4& v);
    Vec4& operator/=(float scalar);
    Vec4& operator/=(const Vec4& v);

    float& operator[](int index);
    float const& operator[](int index) const;

    // Casting operators
    operator Vec2(); // Vec4 to Vec2
    operator Vec3(); // Vec4 to Vec4

    // variables
    float x;
    float y;
    float z;
    float w;
	
 //   struct Color
 //   {
	//	float r;
	//	float g;
	//	float b;
	//	float a;
	//	Color() : r(0), g(0), b(0), a(1) {}

 //       Color(float _r, float _g, float _b, float _a)
 //               : r(_r), g(_g), b(_b), a(_a) {}
 //   };
	//Color GetColor() { return Color(x, y, z, w); }

    static constexpr float kEpsilon = 0.00001f;
    static constexpr float kEpsilonNormalSqrt = 1e-15f;

};
// Operators (unary arithmetic)
Vec4 operator-(const Vec4& v);

// Operators (binary arithmetic)
Vec4 operator+(const Vec4& v, float const& scalar);
Vec4 operator+(float const& scalar, const Vec4& v);
Vec4 operator+(const Vec4& v1, const Vec4& v2);
Vec4 operator-(const Vec4&  v, float const& scalar);
Vec4 operator-(float const& scalar, const Vec4& v);
Vec4 operator-(const Vec4&  v1, const Vec4&  v2);
Vec4 operator*(const Vec4&  v, float const& scalar);
Vec4 operator*(float const& scalar, const Vec4&  v);
Vec4 operator*(const Vec4&  v1, const Vec4&  v2);
Vec4 operator/(const Vec4&  v, float const& scalar);
Vec4 operator/(float const& scalar, const Vec4&  v);

bool operator==(const Vec4& v1, const Vec4& v2);
bool operator!=(const Vec4& v1, const Vec4& v2);

std::ostream& operator<<(std::ostream& os, const Vec4& v);

DLL_API Vec4 floatsToVec4(float x, float y, float z, float w);

} 


#endif // VECTOR4_H