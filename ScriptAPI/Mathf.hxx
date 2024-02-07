#pragma once

#include "../Shared_Libs/TDSMath.h"

namespace ScriptAPI
{
	public ref class Mathf
	{
    public:
        static bool IsFinite(float f);
        static bool IsEqual(float lhs, float rhs, float fEpsilon);
        static bool IsNaN(float f);
        static float Sin(float f);
        static float Cos(float f);
        static float Tan(float f);
        static float Asin(float f);
        static float Acos(float f);
        static float Atan(float f);
        static float Atan2(float y, float x);
        static float Sqrt(float f);
        static float Abs(float f);
        static int Abs(int value);
        static float Mod(float f, float divisor);

        static float Min(float a, float b);
        static int Min(int a, int b);

        static float Max(float a, float b);
        static int Max(int a, int b);

        static float Pow(float f, float p);
        static float Exp(float power);
        static float Log(float f, float p);
        static float Log(float f);
        static float Log2(float f);
        static float Log10(float f);
        static float Ceil(float f);
        static float Floor(float f);
        static float Round(float f);
        static int CeilToInt(float f);
        static int FloorToInt(float f);
        static int RoundToInt(float f);
        static float Sign(float f);

        // Clamps a value between a minimum float and maximum float value.
        static float Clamp(float value, float min, float max);
        //static float Clamp(int value, int min, int max);
        // Clamps value between 0 and 1 and returns value.
        //static float Clamp01(float value);

        // Color Conversion Functions
        static uint8_t ColorFloatToByte(float value);
        static int8_t ColorFloatToSignedByte(float value);

        static float ColorByteToFloat(uint8_t value);
        static float ColorSignedByteToFloat(int8_t value);

        // Linearly interpolates between a and b by t. t is clamped between 0 and 1.
        static float Lerp(float a, float b, float t);

        // Linearly interpolates between a and b by t. t is not clamped.
        static float LerpUnclamped(float a, float b, float t);

        // Same as Lerp but makes sure the values interpolate correctly when they wrap around 360 degrees.
        static float LerpAngle(float a, float b, float t);

        // Moves a value current towards target.
        static float MoveTowards(float current, float target, float maxDelta);

        // Same as MoveTowards but makes sure the values interpolate correctly when they wrap around 360 degrees.
        static float MoveTowardsAngle(float current, float target, float maxDelta);

        // Interpolates between min and max with smoothing at the limits.
        static float SmoothStep(float from, float to, float t);

        // Compares two floating point values if they are similar.
        static bool Approximately(float a, float b);

        // Loops the value t, so that it is never larger than length and never smaller than 0.
        static float Repeat(float t, float length);

        // PingPongs the value t, so that it is never larger than length and never smaller than 0.
        static float PingPong(float t, float length);

        // Calculates the linear parameter t that produces the interpolant value within the range [a, b].
        static float InverseLerp(float a, float b, float value);

        // Calculates the shortest difference between two given angles given in degrees.
        static float DeltaAngle(float current, float target);
	};
}
