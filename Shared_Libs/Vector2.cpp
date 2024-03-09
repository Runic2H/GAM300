#include "Vector2.h"

namespace TDS
{
    Vec2::Vec2() : x(0), y(0) {}
    //Vec2::Vec2(const Vec2& v) : x(v.x), y(v.y) {}
    Vec2::Vec2(float value) : x(value), y(value) {}
    Vec2::Vec2(float data[]) : x(data[0]), y(data[1]) {}
    Vec2::Vec2(float newX, float newY) : x(newX), y(newY) {}
    Vec2::Vec2(const float* newX, const float* newY) : x(*newX), y(*newY) {}
    //Vec2::~Vec2() {}

    Vec2 Vec2::down() { return Vec2(0.f, -1.f); }
    Vec2 Vec2::left() { return Vec2(-1.f, 0.f); }
    Vec2 Vec2::one() { return Vec2(1.f, 1.f); }
    Vec2 Vec2::right() { return Vec2(1.f, 0.f); }
    Vec2 Vec2::up() { return Vec2(0.f, 1.f); }
    Vec2 Vec2::zero() { return Vec2(0.f, 0.f); }
    Vec2 Vec2::positiveInfinity() { return Vec2(INFINITY, INFINITY); }
    Vec2 Vec2::negativeInfinity() { return Vec2(-INFINITY, -INFINITY); }

    float Vec2::magnitude() { return Mathf::Sqrt(x * x + y * y); }
    Vec2 Vec2::normalize() 
    { 
        Vec2 v = Vec2(x, y); 
        v.Normalize(); 
        return v;
    }

    float Vec2::sqrMagnitude() { return x * x + y * y; }   
    bool Vec2::Equals(const Vec2& v) { return x == v.x && y == v.y; }
    void Vec2::Normalize()
    {
        float mag = magnitude();
        if (mag > kEpsilon)
        {
            x /= mag;
            y /= mag;
        }
        else
        {
            x = 0;
            y = 0;
        }
    }
    void Vec2::Set(float newX, float newY) { x = newX; y = newY; }
    std::string Vec2::ToString()
    {
        std::ostringstream oss;
        oss << "Vec2(" << x << ", " << y << ")";
        return oss.str();
    }

    float Vec2::Angle(Vec2 from, Vec2 to)
    {
        float denominator = Mathf::Sqrt(from.sqrMagnitude() * to.sqrMagnitude());
        if (denominator < kEpsilonNormalSqrt)
            return 0;
        float dot = Mathf::Clamp(Dot(from, to) / denominator, -1.f, 1.f);
        return Mathf::Acos(dot);
    }

    Vec2 Vec2::ClampMagnitude(Vec2 vector, float maxLength)
    {
        float sqrMagnitude = vector.sqrMagnitude();
        if (sqrMagnitude > maxLength * maxLength)
        {
            float mag = Mathf::Sqrt(sqrMagnitude);
            float normalizedX = vector.x / mag;
            float normalizedY = vector.y / mag;
            return Vec2(normalizedX * maxLength, normalizedY * maxLength);
        }
        return vector;
    }

    float Vec2::Distance(Vec2 a, Vec2 b)
    {
        float diffX = a.x - b.x;
        float diffY = a.y - b.y;
        return Mathf::Sqrt(diffX * diffX + diffY * diffY);
    }

    float Vec2::Dot(const Vec2 lhs, const Vec2 rhs) 
    { 
        return lhs.x * rhs.x + lhs.y * rhs.y; 
    }

    Vec2 Vec2::Lerp(const Vec2 a, const Vec2 b, float t)
    {
        t = Mathf::Clamp01(t);
        return Vec2(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t);
    }

    Vec2 Vec2::LerpUnclamped(const Vec2 a, const Vec2 b, float t) 
    { 
        return Vec2(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t); 
    }

    Vec2 Vec2::Max(const Vec2 lhs, const Vec2 rhs) 
    { 
        return Vec2(Mathf::Max(lhs.x, rhs.x), Mathf::Max(lhs.y, rhs.y)); 
    }

    Vec2 Vec2::Min(const Vec2 lhs, const Vec2 rhs) 
    { 
        return Vec2(Mathf::Min(lhs.x, rhs.x), Mathf::Min(lhs.y, rhs.y)); 
    }

    Vec2 Vec2::MoveTowards(const Vec2 current, const Vec2 target, float maxDistanceDelta)
    {
        float toVectorX = target.x - current.x;
        float toVectorY = target.y - current.y;

        float sqDist = toVectorX * toVectorX + toVectorY * toVectorY;

        if (sqDist == 0 || (maxDistanceDelta >= 0 && sqDist <= maxDistanceDelta * maxDistanceDelta))
            return target;
        float dist = Mathf::Sqrt(sqDist);
        return Vec2(current.x + toVectorX / dist * maxDistanceDelta, current.y + toVectorY / dist * maxDistanceDelta);
    }

    Vec2 Vec2::Perpendicular(const Vec2 inDirection) 
    { 
        return Vec2(-inDirection.y, inDirection.x);
    }

    Vec2 Vec2::Project(Vec2 vector, Vec2 onNormal)
    {
        float sqrMag = Dot(onNormal, onNormal);
        if (sqrMag < kEpsilonNormalSqrt)
            return zero();
        float dot = Dot(vector, onNormal);
        return Vec2(onNormal.x * dot / sqrMag, onNormal.y * dot / sqrMag);
    }
    Vec2 Vec2::Reflect(Vec2 inDirection, Vec2 inNormal)
    {
        inNormal.Normalize();
        return -2 * Dot(inNormal, inDirection) * inNormal + inDirection;
    }


    Vec2 Vec2::Scale(const Vec2 a, const Vec2 b) { return Vec2(a.x * b.x, a.y * b.y); }

    void Vec2::Scale(const Vec2 scale) { x *= scale.x; y *= scale.y; }

    float Vec2::SignedAngle(Vec2 from, Vec2 to)
    {
        float unsignedAngle = Angle(from, to);
        float sign = Mathf::Sign(from.x * to.y - from.y * to.x);
        return unsignedAngle * sign;
    }

    Vec2& Vec2::operator=(const Vec2& v) 
    {
        x = v.x;
        y = v.y;
        return *this;
    }

    Vec2& Vec2::operator+=(float scalar) 
    {
        x += scalar;
        y += scalar;
        return *this;
    }

    Vec2& Vec2::operator+=(const Vec2& v) 
    {
        x += v.x;
        y += v.y;
        return *this;
    }

    Vec2& Vec2::operator-=(float scalar) 
    {
        x -= scalar;
        y -= scalar;
        return *this;
    }

    Vec2& Vec2::operator-=(const Vec2& v) 
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    Vec2& Vec2::operator*=(float scalar) 
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vec2& Vec2::operator*=(const Vec2& v) 
    {
        x *= v.x;
        y *= v.y;
        return *this;
    }

    Vec2& Vec2::operator/=(float scalar) 
    {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    Vec2& Vec2::operator/=(const Vec2& v) 
    {
        x /= v.x;
        y /= v.y;
        return *this;
    }

    float& Vec2::operator[](int index) 
    {
        switch (index)
        {
            case 0: return x;
            case 1: return y;
            default: throw std::out_of_range("Index out of range");
        }
    }

    float const& Vec2::operator[](int index) const
    {
        switch (index)
        {
            case 0: return x;
            case 1: return y;
            default: throw std::out_of_range("Index out of range");
        }
    }

    Vec2::operator Vec3() { return Vec3(x, y, 0); }
    Vec2::operator Vec4() { return Vec4(x, y, 0, 0); }

    std::ostream& operator<<(std::ostream& os, const Vec2& v)
    {
        os << "(" << v.x << ", " << v.y << ")";
        return os;
    }

    Vec2 operator-(const Vec2& v) 
    {
        return Vec2(-v.x, -v.y);
    }

    Vec2 operator+(const Vec2& v, float const& scalar) 
    {
        return Vec2(v.x + scalar, v.y + scalar);
    }

    Vec2 operator+(float const& scalar, const Vec2& v) 
    {
        return Vec2(v.x + scalar, v.y + scalar);
    }

    Vec2 operator+(const Vec2& v1, const Vec2& v2) 
    {
        return Vec2(v1.x + v2.x, v1.y + v2.y);
    }

    Vec2 operator-(const Vec2& v, float const& scalar) 
    {
        return Vec2(v.x - scalar, v.y - scalar);
    }

    Vec2 operator-(float const& scalar, const Vec2& v) 
    {
        return Vec2(scalar - v.x, scalar - v.y);
    }

    Vec2 operator-(const Vec2& v1, const Vec2& v2) 
    {
        return Vec2(v1.x - v2.x, v1.y - v2.y);
    }

    Vec2 operator*(const Vec2& v, float const& scalar) 
    {
        return Vec2(v.x * scalar, v.y * scalar);
    }

    Vec2 operator*(float const& scalar, const Vec2& v) 
    {
        return Vec2(v.x * scalar, v.y * scalar);
    }

    Vec2 operator*(const Vec2& v1, const Vec2& v2) 
    {
        return Vec2(v1.x * v2.x, v1.y * v2.y);
    }

    Vec2 operator/(const Vec2& v, float const& scalar) 
    {
        return Vec2(v.x / scalar, v.y / scalar);
    }

    Vec2 operator/(float const& scalar, const Vec2& v) 
    {
        return Vec2(scalar / v.x, scalar / v.y);
    }

    bool operator==(const Vec2& v1, const Vec2& v2) 
    {
        return v1.x == v2.x && v1.y == v2.y;
    }

    bool operator!=(const Vec2& v1, const Vec2& v2) 
    {
        return v1.x != v2.x || v1.y != v2.y;
    }

    Vec2 floatsToVec2(float x, float y)
    {
        return Vec2(x, y);
    }

}  // namespace WD