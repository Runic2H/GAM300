#include "MathCommon.h"
namespace TDS
{
    float Mathf::Clamp(float value, float min, float max)
    {
        if (value < min)
            return min;
        else if (value > max)
            return max;
        else
            return value;
    }
    float Mathf::ClampScriptAPI(float value, float min, float max)
    {
        if (value < min)
            return min;
        else if (value > max)
            return max;
        else
            return value;
    }

    //float Mathf::Clamp(int value, int min, int max)
    //{
    //    if (value < min)
    //        return static_cast<float>(min);
    //    else if (value > max)
    //        return static_cast<float>(max);
    //    else
    //        return static_cast<float>(value);
    //}

    float Mathf::Clamp01(float value)
    {
        if (value < 0.f)
            return 0.f;
        else if (value > 1.f)
            return 1.f;
        else
            return value;
    }

    uint8_t Mathf::ColorFloatToByte(float value)
    {
        if (IsNaN(value))
            return 0;
        else
        {
            value = Clamp01(value);
			return static_cast<uint8_t>(value * 255.f + 0.5f);
        }
    }

    int8_t Mathf::ColorFloatToSignedByte(float value)
    {
        if (IsNaN(value))
            return 0;
        else
        {
            value = Clamp(value, -1.f, 1.f) * 127.0f;
            if (value >= 0.0f)
            {
                value += 0.5f;
            }
            else
            {
				value -= 0.5f;
            }
            return static_cast<int8_t>(value);
        }
    }

    float Mathf::ColorByteToFloat(uint8_t value)
    {
		return value * (1.f / 255.f);
    }

    float Mathf::ColorSignedByteToFloat(int8_t value)
    {
        return (value == -128) ? -1.0f : value * (1.0f / 127.0f);
    }

    float Mathf::Lerp(float a, float b, float t)
    {
        return a + (b - a) * Clamp01(t);
    }

    float Mathf::LerpUnclamped(float a, float b, float t)
    {
        return a + (b - a) * t;
    }

    float Mathf::LerpAngle(float a, float b, float t) {
        float delta = Mathf::Repeat((b - a), 360.f);
        if (delta > 180.f)
            delta -= 360.f;
        return a + delta * Clamp01(t);
    }

    float Mathf::MoveTowards(float current, float target, float maxDelta)
    {
        if (Abs(target - current) <= maxDelta)
            return target;
        return current + Sign(target - current) * maxDelta;
    }

    float Mathf::MoveTowardsAngle(float current, float target, float maxDelta)
    {
        float deltaAngle = DeltaAngle(current, target);
        if (-maxDelta < deltaAngle && deltaAngle < maxDelta)
            return target;
        target = current + deltaAngle;
        return MoveTowards(current, target, maxDelta);
    }

    float Mathf::SmoothStep(float from, float to, float t)
    {
        t = Clamp01(t);
        t = -2.f * t * t * t + 3.f * t * t;
        return to * t + from * (1.f - t);
    }

    bool Mathf::Approximately(float a, float b)
    {
        //return Abs(b - a) < Max(0.000001f * Max(Abs(a), Abs(b)), Mathf::Epsilon * 100);
        return Abs(a - b ) < Mathf::Epsilon * (1 + (std::max)( Abs(a), Abs(b) ) );
    }

    float Mathf::Repeat(float t, float length)
    {
        return Clamp(t - Floor(t / length) * length, 0.f, length);
    }

    float Mathf::PingPong(float t, float length)
    {
        t = Repeat(t, length * 2.f);
        return length - Abs(t - length);
    }

    float Mathf::InverseLerp(float a, float b, float value)
    {
        if (a != b)
            return Clamp01((value - a) / (b - a));
        else
            return 0.f;
    }

    float Mathf::DeltaAngle(float current, float target)
    {
        float delta = Repeat((target - current), 360.f);
        if (delta > 180.f)
            delta -= 360.f;
        return delta;
    }
} // namespace WD