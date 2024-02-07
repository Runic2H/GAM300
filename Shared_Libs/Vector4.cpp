#include "Vector4.h"

namespace TDS
{
    Vec4::Vec4() : x(0.f), y(0.f), z(0.f), w(0.f) {}
    Vec4::Vec4(const Vec4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
    Vec4::Vec4(float value) : x(value), y(value), z(value), w(value) {}
    Vec4::Vec4(float data[]) : x(data[0]), y(data[1]), z(data[2]), w(data[3]) {}
    Vec4::Vec4(float newX, float newY, float newZ, float newW) : x(newX), y(newY), z(newZ), w(newW) {}
    Vec4::Vec4(const Vec2& v, float newZ, float newW) : x(v.x), y(v.y), z(newZ), w(newW) {}
    Vec4::Vec4(const Vec3& v, float newW) : x(v.x), y(v.y), z(v.z), w(newW) {}
    Vec4::Vec4(const float* newX, const float* newY, const float* newZ, const float* newW) : x(*newX), y(*newY), z(*newZ), w(*newW) {}
    //Vec4::~Vec4() {}

    Vec4 Vec4::one() { return Vec4(1.f, 1.f, 1.f, 1.f); }
    Vec4 Vec4::zero() { return Vec4(0.f, 0.f, 0.f, 0.f); }
    Vec4 Vec4::positiveInfinity() { return Vec4(INFINITY, INFINITY, INFINITY, INFINITY); }
    Vec4 Vec4::negativeInfinity() { return Vec4(-INFINITY, -INFINITY, -INFINITY, -INFINITY); }

    float Vec4::magnitude() { return Mathf::Sqrt(x * x + y * y + z * z + w * w); }
    Vec4 Vec4::normalize() { return Vec4::Normalize(*this); }
    float Vec4::sqrMagnitude() { return x * x + y * y + z * z + w * w; }

    bool Vec4::Equals(const Vec4& v) { return x == v.x && y == v.y && z == v.z && w == v.w; }
    void Vec4::Normalize()
    {
        float mag = magnitude();
        if (mag > kEpsilon)
        {
            x /= mag;
            y /= mag;
            z /= mag;
            w /= mag;
        }
        else
        {
            x = 0.f;
            y = 0.f;
            z = 0.f;
            w = 0.f;
        }
    }

    void Vec4::Set(float newX, float newY, float newZ, float newW) { x = newX; y = newY; z = newZ; w = newW; }
    std::string Vec4::ToString()
    {
        std::ostringstream oss;
        oss << "Vec4(" << x << ", " << y << ", " << z << ", " << w << ")";
        return oss.str();
    }

    float Vec4::Distance(Vec4 a, Vec4 b) { return (a - b).magnitude(); }
    float Vec4::Dot(const Vec4 lhs, const Vec4 rhs) { return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w; }

    Vec4 Vec4::Lerp(const Vec4 a, const Vec4 b, float t)
    {
        t = Mathf::Clamp01(t);
        return Vec4(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.z + (b.z - a.z) * t, a.w + (b.w - a.w) * t);
    }

    Vec4 Vec4::LerpUnclamped(const Vec4 a, const Vec4 b, float t)
    {
        return Vec4(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.z + (b.z - a.z) * t, a.w + (b.w - a.w) * t);
    }

    Vec4 Vec4::Max(const Vec4 lhs, const Vec4 rhs)
    {
        return Vec4(Mathf::Max(lhs.x, rhs.x), Mathf::Max(lhs.y, rhs.y), Mathf::Max(lhs.z, rhs.z), Mathf::Max(lhs.w, rhs.w));
    }

    Vec4 Vec4::Min(const Vec4 lhs, const Vec4 rhs)
    {
        return Vec4(Mathf::Min(lhs.x, rhs.x), Mathf::Min(lhs.y, rhs.y), Mathf::Min(lhs.z, rhs.z), Mathf::Min(lhs.w, rhs.w));
    }

    Vec4 Vec4::MoveTowards(Vec4 current, Vec4 target, float maxDistanceDelta)
    {
        float toVector_x = target.x - current.x;
        float toVector_y = target.y - current.y;
        float toVector_z = target.z - current.z;
        float toVector_w = target.w - current.w;

        float sqdist = toVector_x * toVector_x + 
                    toVector_y * toVector_y + 
                    toVector_z * toVector_z + 
                    toVector_w * toVector_w;

        if (sqdist == 0 || (maxDistanceDelta >= 0 && sqdist <= maxDistanceDelta * maxDistanceDelta))
            return target;
        float dist = Mathf::Sqrt(sqdist);

        return Vec4(current.x + toVector_x / dist * maxDistanceDelta,
            current.y + toVector_y / dist * maxDistanceDelta,
            current.z + toVector_z / dist * maxDistanceDelta,
            current.w + toVector_w / dist * maxDistanceDelta);
    }

    Vec4 Vec4::Normalize(Vec4 value)
    {
        float mag = value.magnitude();
        if (mag > kEpsilon)
        {
            return Vec4(value.x / mag, value.y / mag, value.z / mag, value.w / mag);
        }
        else
        {
            return Vec4::zero();
        }
    }

    Vec4 Vec4::Project(Vec4 vector, Vec4 onNormal)
    {
        float sqrMag = Dot(onNormal, onNormal);
        if (sqrMag < kEpsilon)
            return Vec4::zero();
        else
            return onNormal * Dot(vector, onNormal) / sqrMag;
    }

    Vec4 Vec4::Scale(Vec4 a, Vec4 b) { return Vec4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w); }
    void Vec4::Scale(Vec4 scale) { x *= scale.x; y *= scale.y; z *= scale.z; w *= scale.w; }    

    Vec4& Vec4::operator=(const Vec4& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
        w = v.w;
        return *this;
    }

    Vec4& Vec4::operator+=(float scalar)
    {
        x += scalar;
        y += scalar;
        z += scalar;
        w += scalar;
        return *this;
    }

    Vec4& Vec4::operator+=(const Vec4& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        w += v.w;
        return *this;
    }

    Vec4& Vec4::operator-=(float scalar) 
    {
        x -= scalar;
        y -= scalar;
        z -= scalar;
        w -= scalar;
        return *this;
    }

    Vec4& Vec4::operator-=(const Vec4& v) 
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        w -= v.w;
        return *this;
    }

    Vec4& Vec4::operator*=(float scalar) 
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;
        return *this;
    }

    Vec4& Vec4::operator*=(const Vec4& v) 
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        w *= v.w;
        return *this;
    }

    Vec4& Vec4::operator/=(float scalar) 
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        w /= scalar;
        return *this;
    }

    Vec4& Vec4::operator/=(const Vec4& v) 
    {
        x /= v.x;
        y /= v.y;
        z /= v.z;
        w /= v.w;
        return *this;
    }

    float& Vec4::operator[](int index)
    {
        switch (index)
        {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
        default: throw std::out_of_range("Vec4 index out of range.");
        }
    }

    float const& Vec4::operator[](int index) const
    {
        switch (index)
        {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
        default: throw std::out_of_range("Vec4 index out of range.");

        }
    }

    Vec4 operator-(const Vec4& v) { return Vec4(-v.x, -v.y, -v.z, -v.w); }
    Vec4 operator+(const Vec4& v, float const& scalar)
    {
        return Vec4(v.x + scalar, v.y + scalar, v.z + scalar, scalar);
    }
    Vec4 operator+(float const& scalar, const Vec4& v)
    {
        return Vec4(scalar + v.x, scalar + v.y, scalar + v.z, scalar + v.w);
    }
    Vec4 operator+(const Vec4& lhs, const Vec4& rhs)
    {
        return Vec4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
    }
    Vec4 operator-(const Vec4& v, float const& scalar)
    {
        return Vec4(v.x - scalar, v.y - scalar, v.z - scalar, v.w - scalar);
    }
    Vec4 operator-(float const& scalar, const Vec4& v)
    {
        return Vec4(scalar - v.x, scalar - v.y, scalar - v.z, scalar - v.w);
    }

    Vec4 operator-(const Vec4& lhs, const Vec4& rhs)
    {
        return Vec4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
    }

    Vec4 operator*(const Vec4& v, float const& scalar)
    {
        return Vec4(v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar);
    }

    Vec4 operator*(float const& scalar, const Vec4& v)
    {
        return Vec4(scalar * v.x, scalar * v.y, scalar * v.z, scalar * v.w);
    }

    Vec4 operator*(const Vec4& lhs, const Vec4& rhs)
    {
        return Vec4(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w);
    }

    Vec4 operator/(const Vec4& v, float const& scalar)
    {
        return Vec4(v.x / scalar, v.y / scalar, v.z / scalar, v.w / scalar);
    }

    Vec4 operator/(float const& scalar, const Vec4& v)
    {
        return Vec4(scalar / v.x, scalar / v.y, scalar / v.z, scalar / v.w);
    }

    bool operator==(const Vec4& lhs, const Vec4& rhs)
    {
        return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
    }

    bool operator!=(const Vec4& lhs, const Vec4& rhs)
    {
        return !(lhs == rhs);
    }

    std::ostream& operator<<(std::ostream& os, const Vec4& v) 
    {
        os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
        return os;
    }
    Vec4::operator Vec2() { return Vec2(x, y); }
    Vec4::operator Vec3() { return Vec3(x, y, z); }

    Vec4 floatsToVec4(float x, float y, float z, float w)
    {
        return Vec4(x, y, z, w);
    }

}  // namespace WD