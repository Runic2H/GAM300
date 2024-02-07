#include "Mathf.hxx"
#include <algorithm>

namespace ScriptAPI
{
    bool Mathf::IsFinite(float f)
    {
        return TDS::Mathf::IsFinite(f);
    }
    bool Mathf::IsEqual(float lhs, float rhs, float fEpsilon)
    {
        return TDS::Mathf::IsEqual(lhs, rhs, fEpsilon);
    }
    bool Mathf::IsNaN(float f)
    {
        return TDS::Mathf::IsNaN(f);
    }
    float Mathf::Sin(float f)
    {
        return TDS::Mathf::Sin(f);
    }
    float Mathf::Cos(float f)
    {
        return TDS::Mathf::Cos(f);
    }
    float Mathf::Tan(float f)
    {
        return TDS::Mathf::Tan(f);
    }
    float Mathf::Asin(float f)
    {
        return TDS::Mathf::Asin(f);
    }
    float Mathf::Acos(float f)
    {
        return TDS::Mathf::Acos(f);
    }
    float Mathf::Atan(float f)
    {
        return TDS::Mathf::Atan(f);
    }
    float Mathf::Atan2(float y, float x)
    {
        return TDS::Mathf::Atan2(y, x);
    }
    float Mathf::Sqrt(float f)
    {
        return TDS::Mathf::Sqrt(f);
    }
    float Mathf::Abs(float f)
    {
        return TDS::Mathf::Abs(f);
    }
    int Mathf::Abs(int value)
    {
        return TDS::Mathf::Abs(value);
    }
    float Mathf::Mod(float f, float divisor)
    {
        return TDS::Mathf::Mod(f, divisor);
    }

    float Mathf::Min(float a, float b)
    {
        return TDS::Mathf::Min(a, b);
    }
    int Mathf::Min(int a, int b)
    {
        return TDS::Mathf::Min(a, b);
    }

    float Mathf::Max(float a, float b)
    {
        return TDS::Mathf::Max(a, b);
    }
    int Mathf::Max(int a, int b)
    {
        return TDS::Mathf::Max(a, b);
    }

    float Mathf::Pow(float f, float p)
    {
        return TDS::Mathf::Pow(f, p);
    }
    float Mathf::Exp(float power)
    {
        return TDS::Mathf::Exp(power);
    }
    float Mathf::Log(float f, float p)
    {
        return TDS::Mathf::Log(f, p);
    }
    float Mathf::Log(float f)
    {
        return TDS::Mathf::Log(f);
    }
    float Mathf::Log2(float f)
    {
        return TDS::Mathf::Log2(f);
    }
    float Mathf::Log10(float f)
    {
        return TDS::Mathf::Log10(f);
    }
    float Mathf::Ceil(float f)
    {
        return TDS::Mathf::Ceil(f);
    }
    float Mathf::Floor(float f)
    {
        return TDS::Mathf::Floor(f);
    }
    float Mathf::Round(float f)
    {
        return TDS::Mathf::Round(f);
    }
    int Mathf::CeilToInt(float f)
    {
        return TDS::Mathf::CeilToInt(f);
    }
    int Mathf::FloorToInt(float f)
    {
        return TDS::Mathf::FloorToInt(f);
    }
    int Mathf::RoundToInt(float f)
    {
        return TDS::Mathf::RoundToInt(f);
    }
    float Mathf::Sign(float f)
    {
        return TDS::Mathf::Sign(f);
    }

    // Clamps a value between a minimum float and maximum float value.
    float Mathf::Clamp(float value, float min, float max)
    {
        return TDS::Mathf::ClampScriptAPI(value, min, max);
    }
    //float Mathf::Clamp(int value, int min, int max)
    //{
    //    return std::clamp(value, min, max);
    //}
    // Clamps value between 0 and 1 and returns value.
    //float Mathf::Clamp01(float value)
    //{
    //    return TDS::Mathf::Clamp01(value);
    //}

    // Color Conversion Functions
    uint8_t Mathf::ColorFloatToByte(float value)
    {
        return TDS::Mathf::ColorFloatToByte(value);
    }
    int8_t Mathf::ColorFloatToSignedByte(float value)
    {
        return TDS::Mathf::ColorFloatToSignedByte(value);
    }

    float Mathf::ColorByteToFloat(uint8_t value)
    {
        return TDS::Mathf::ColorByteToFloat(value);
    }
    float Mathf::ColorSignedByteToFloat(int8_t value)
    {
        return TDS::Mathf::ColorSignedByteToFloat(value);
    }

    // Linearly interpolates between a and b by t. t is clamped between 0 and 1.
    float Mathf::Lerp(float a, float b, float t)
    {
        return TDS::Mathf::Lerp(a, b, t);
    }

    // Linearly interpolates between a and b by t. t is not clamped.
    float Mathf::LerpUnclamped(float a, float b, float t)
    {
        return TDS::Mathf::LerpUnclamped(a, b, t);
    }

    // Same as Lerp but makes sure the values interpolate correctly when they wrap around 360 degrees.
    float Mathf::LerpAngle(float a, float b, float t)
    {
        return TDS::Mathf::LerpAngle(a, b, t);
    }

    // Moves a value current towards target.
    float Mathf::MoveTowards(float current, float target, float maxDelta)
    {
        return TDS::Mathf::MoveTowards(current, target, maxDelta);
    }

    // Same as MoveTowards but makes sure the values interpolate correctly when they wrap around 360 degrees.
    float Mathf::MoveTowardsAngle(float current, float target, float maxDelta)
    {
        return TDS::Mathf::MoveTowardsAngle(current, target, maxDelta);
    }

    // Interpolates between min and max with smoothing at the limits.
    float Mathf::SmoothStep(float from, float to, float t)
    {
        return TDS::Mathf::SmoothStep(from, to, t);
    }

    // Compares two floating point values if they are similar.
    bool Mathf::Approximately(float a, float b)
    {
        return TDS::Mathf::Approximately(a, b);
    }

    // Loops the value t, so that it is never larger than length and never smaller than 0.
    float Mathf::Repeat(float t, float length)
    {
        return TDS::Mathf::Repeat(t, length);
    }

    // PingPongs the value t, so that it is never larger than length and never smaller than 0.
    float Mathf::PingPong(float t, float length)
    {
        return TDS::Mathf::PingPong(t, length);
    }

    // Calculates the linear parameter t that produces the interpolant value within the range [a, b].
    float Mathf::InverseLerp(float a, float b, float value)
    {
        return TDS::Mathf::InverseLerp(a, b, value);
    }

    // Calculates the shortest difference between two given angles given in degrees.
    float Mathf::DeltaAngle(float current, float target)
    {
        return TDS::Mathf::DeltaAngle(current, target);
    }
}
