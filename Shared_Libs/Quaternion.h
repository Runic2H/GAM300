#ifndef QUATERNION_H
#define QUATERNION_H

#include "Matrix3.h"
#include "Matrix4.h"

// layout:
// x
// y
// z
// w

namespace TDS
{
class Mat3;
class Mat4;
class Quat
{
    public:
    // Constructors and destructors
    Quat();
    Quat(Quat const& q); // Copy constructor
    Quat(float value); // Constructor with one value
    Quat(float data[]); // Constructor with array of values
    Quat(float newX, float newY, float newZ, float newW); // Constructor with four values
    Quat(float angle, Vec3 const& axis); // Constructor with angle and axis
    Quat(Vec3 const& u, Vec3 const& v); // Constructor with two vectors
    Quat(Vec3 const& euler); // Constructor with euler angles in radians
    //~Quat();

    // Functions

    // Returns the q rotation angle
    static float angle(Quat const& q);
    // Build a quaternion from an angle and an axis
    static Quat angleAxis(float const& angle, float const& x, float const& y, float const& z);
    static Quat angleAxis(float const& angle, Vec3 const& axis);
    // Returns the q rotation axis
    static Vec3 axis(Quat const& q);
    // Returns the q conjugate
    static Quat conjugate(Quat const& q);
    // Returns the cross product of q1 and q2
    static Quat cross(Quat const& q1, Quat const& q2);
    // Compute cross product of q and v
    static Vec3 cross(Quat const& q, Vec3 const& v);
    // Compute cross product of v and q
    static Vec3 cross(Vec3 const& v, Quat const& q);
    // Returns the dot product of q1 and q2
    static float dot(Quat const& q1, Quat const& q2);
    // Return euler angle, pitch as x, yaw as y, roll as z
    static Vec3 eulerAngle(Quat const& q);
    // Returns a exp of a quaternion
    static Quat exp(Quat const& q);
    // Extract the real component of q
    static float extractRealComponent(Quat const& q);
    static Quat fromTo(const Vec3& from, const Vec3& to);
    // Returns an intermediate control pt for squad interpolation
    static Quat intermediate(Quat const& prev, Quat const& curr, Quat const& next);
    // Returns the inverse of q
    static Quat inverse(Quat const& q);
    // Returns the length of q
    static float length(Quat const& q);
    // Returns the squared length of q
    static float length2(Quat const& q);
    // Returns the log of a quaternion
    static Quat log(Quat const& q);
    static Quat lookRotation(const Vec3& direction, const Vec3& up);
    // Return a SLERP interpolated quaternion of x and y according to a
    static Quat mix(Quat const& x, Quat const& y, float a);
    static Quat nlerp(const Quat& from, const Quat& to, float t);
    // Returns a normalized quaternion
    static Quat normalize(Quat const& q);
    // Return pitch value of euler angles
    static float pitch(Quat const& q);
    // Return x raised to the y power
    static Quat pow(Quat const& q, float const& exponent);
    // Return roll value of euler angles
    static float roll(Quat const& q);
    // Return Quaternion square root
    static Vec3 rotate(Quat const& q, Vec3 const& v);
    // Rotates a 4 components vector by a quaternion
    static Vec4 rotate(Quat const& q, Vec4 const& v);
    // Rotates a quaternion from an vector of 3 components axis and an angle expressed in degree
    static Quat rotate(Quat const& q, float const& angle, Vec3 const& axis);
    // Compute a point on a path according squad equation
    static Quat squad(Quat const& q1, Quat const& q2, Quat const& s1, Quat const& s2, float const& h);
    // Converts quaternion to matrix
    static Mat3 toMat3(Quat const& q);
    static Mat4 toMat4(Quat const& q);
    // Return yaw value of euler angles
    static float yaw(Quat const& q);
    
    // Component Access
    float& operator[](int index);
    float const& operator[](int index) const;

    // Operators (unary arithmetic)
    Quat& operator=(Quat const& q);
    Quat& operator+=(Quat const& q);
    Quat& operator-=(Quat const& q);
    Quat& operator*=(Quat const& q);
    Quat& operator*=(float f);
    Quat& operator/=(float f);

    // Variables
    float x;
    float y;
    float z;
    float w;
};

// Operators (unabry bit arithmetic)
Quat operator-(Quat const& q);

// Operators (binary arithmetic)
Quat operator+(Quat const& q1, Quat const& q2);
Quat operator-(Quat const& q1, Quat const& q2);
Quat operator*(Quat const& q1, Quat const& q2);
Vec3 operator*(Quat const& q, Vec3 const& v);
//Vec3 operator*(Vec3 const& v, Quat const& q);
Vec4 operator*(Quat const& q, Vec4 const& v);
Vec4 operator*(Vec4 const& v, Quat const& q);
Quat operator*(Quat const& q, float const& f);
Quat operator*(float const& f, Quat const& q);
Quat operator/(Quat const& q, float const& f);

// boolean operator
bool operator==(Quat const& q1, Quat const& q2);
bool operator!=(Quat const& q1, Quat const& q2);

DLL_API Quat floatsToQuat(float x, float y, float z, float w);

} // namespace WD

#endif // QUATERNION_H