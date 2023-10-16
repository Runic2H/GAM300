#include "Color.h"

namespace TDS
{
	Color::Color()
	{
		const float TypeNaN = Mathf::NaN;
		r = TypeNaN;
		g = TypeNaN;
		b = TypeNaN;
		a = TypeNaN;
	}
	constexpr Color::Color(float fLinearRed, float fLinearGreen, float fLinearBlue, float fLinearAlpha)
		: r(fLinearRed)
		, g(fLinearGreen)
		, b(fLinearBlue)
		, a(fLinearAlpha)
	{}

	Color::Color(const ColorLinear & cc)
	{
		*this = cc;
	}

	Color::Color(const ColorGamma& cc)
	{
		*this = cc;
	}

	void Color::SetRGB(float fLinearRed, float fLinearGreen, float fLinearBlue)
	{
		r = fLinearRed;
		g = fLinearGreen;
		b = fLinearBlue;
	}

	void Color::SetRGBA(float fLinearRed, float fLinearGreen, float fLinearBlue, float fLinearAlpha)
	{
		r = fLinearRed;
		g = fLinearGreen;
		b = fLinearBlue;
		a = fLinearAlpha;
	}

	Color Color::SetZero()
	{
		return Color(0.0f, 0.0f, 0.0f, 0.0f);
	}

	Color Color::SetNaN()
	{
		const float TypeNaN = Mathf::NaN;
		return Color(TypeNaN, TypeNaN, TypeNaN, TypeNaN);
	}

	Color Color::SetHSV(float fHue, float fSat, float fVal)
	{
		float c = fSat * fVal;
		float x = c * (1.0f - Mathf::Abs(Mathf::Mod(fHue / 60.0f, 2.0f) - 1.0f));
		float m = fVal - c;
		
		Color res;
		res.a = 1.0f;

		if (fHue < 60)
		{
			res.r = c + m;
			res.g = x + m;
			res.b = 0 + m;
		}
		else if (fHue < 120)
		{
			res.r = x + m;
			res.g = c + m;
			res.b = 0 + m;
		}
		else if (fHue < 180)
		{
			res.r = 0 + m;
			res.g = c + m;
			res.b = x + m;
		}
		else if (fHue < 240)
		{
			res.r = 0 + m;
			res.g = x + m;
			res.b = c + m;
		}
		else if (fHue < 300)
		{
			res.r = x + m;
			res.g = 0 + m;
			res.b = c + m;
		}
		else
		{
			res.r = c + m;
			res.g = 0 + m;
			res.b = x + m;
		}

		// The formula above produces value in gamma space
		res.r = GammaToLinear(res.r);
		res.g = GammaToLinear(res.g);
		res.b = GammaToLinear(res.b);

		return res;
	}

	void Color::GetHSV(float& fHue, float& fSat, float& fVal) const
	{
		const float r2 = LinearToGamma(r);
		const float g2 = LinearToGamma(g);
		const float b2 = LinearToGamma(b);

		fVal = Mathf::Max(r2, g2, b2);
		
		if (fVal < Mathf::Epsilon)
		{
			fHue = 0.0f;
			fSat = 0.0f;
			fVal = 0.0f;
			return;
		}

		const float invV = 1.0f / fVal;
		float norm_r = r2 * invV;
		float norm_g = g2 * invV;
		float norm_b = b2 * invV;
		float rgb_min = Mathf::Min(norm_r, norm_g, norm_b);
		float rgb_max = Mathf::Max(norm_r, norm_g, norm_b);

		fSat = rgb_max - rgb_min;
		
		if (fSat == 0)
		{
			fHue = 0.0f;
			return;
		}

		// Normalize saturation
		const float rgb_deltaInv = 1.0f / (rgb_max - rgb_min);
		norm_r = (norm_r - rgb_min) * rgb_deltaInv;
		norm_g = (norm_g - rgb_min) * rgb_deltaInv;
		norm_b = (norm_b - rgb_min) * rgb_deltaInv;
		rgb_max = Mathf::Max(norm_r, norm_g, norm_b);

		// hue
		if (rgb_max == norm_r)
		{
			fHue = 60.0f * (norm_g - norm_b);
			if (fHue < 0.0f)
			{
				fHue += 360.0f;
			}
		}
		else if (rgb_max == norm_g)
		{
			fHue = 120.0f + 60.0f * (norm_b - norm_r);
		}
		else
		{
			fHue = 240.0f + 60.0f * (norm_r - norm_g);
		}
	}

	const Vec4 Color::GetAsVec4() const
	{
		return Vec4(r,g,b,a);
	}

	float Color::GammaToLinear(float fGamma)
	{
		return fGamma <= 0.04045f ? (fGamma / 12.92f) : (Mathf::Pow((fGamma + 0.055f) / 1.055f, 2.4f));
	}

	float Color::LinearToGamma(float fLinear)
	{
		// assuming we have linear color (not CIE xyY or CIE XYZ)
		return fLinear <= 0.0031308f ? (12.92f * fLinear) : (1.055f * Mathf::Pow(fLinear, 1.0f / 2.4f) - 0.055f);
	}

	Vec3 Color::GammaToLinear(const Vec3& vGamma)
	{
		return Vec3(GammaToLinear(vGamma.x), GammaToLinear(vGamma.y), GammaToLinear(vGamma.z));
	}

	Vec3 Color::LinearToGamma(const Vec3& vLinear)
	{
		return Vec3(LinearToGamma(vLinear.x), LinearToGamma(vLinear.y), LinearToGamma(vLinear.z));
	}

	bool Color::IsNormalized() const
	{
		return r >= 0.0f && r <= 1.0f &&
			   g >= 0.0f && g <= 1.0f &&
			   b >= 0.0f && b <= 1.0f &&
			   a >= 0.0f && a <= 1.0f;
	}

	float Color::CalcAverageRGB() const
	{
		return (1.0f / 3.0f) * (r + g + b);
	}

	float Color::GetSaturation() const
	{
		float hue, sat, val;
		GetHSV(hue, sat, val);
		return sat;
	}

	// http://en.wikipedia.org/wiki/Luminance_%28relative%29
	float Color::GetLuminance() const
	{
		return 0.2126f * r + 0.7152f * g + 0.0722f * b;
	}

	Color Color::GetInvertedColor() const
	{
		if (IsNormalized()) throw std::exception("Cannot invert a color that has value outside [0,1] range");
		return Color(1.0f - r, 1.0f - g, 1.0f - b, 1.0f - a);
	}

	Color Color::GetComplementaryColor() const
	{
		float hue, sat, val;
		GetHSV(hue, sat, val);

		Color Shifted = Color::SetHSV(Mathf::Mod(hue + 180.0f, 360.0f), sat, val);
		Shifted.a = a;

		return Shifted;
	}

	void Color::ScaleRGB(float fFactor)
	{
		r *= fFactor;
		g *= fFactor;
		b *= fFactor;
	}

	float Color::ComputeHdrMultiplier() const
	{
		return Mathf::Max(1.0f, r, g, b);
	}

	float Color::ComputeHdrExposureValue() const
	{
		return Mathf::Log2(ComputeHdrMultiplier());
	}

	void Color::ApplyHdrExposureValue(float fEv)
	{
		const float factor = Mathf::Pow(2.0f, fEv);
		r *= factor;
		g *= factor;
		b *= factor;
	}

	void Color::NormalizeToLdrRange()
	{
		ScaleRGB(1.0f / ComputeHdrMultiplier());
	}

	Color Color::GetDarker(float fFactor /* = 2.0f*/) const
	{
		float hue, sat, val;
		GetHSV(hue, sat, val);
		return Color::SetHSV(hue, sat, val / fFactor);
	}

	bool Color::IsNaN() const
	{
		if (Mathf::IsNaN(r))
			return true;
		if (Mathf::IsNaN(g))
			return true;
		if (Mathf::IsNaN(b))
			return true;
		if (Mathf::IsNaN(a))
			return true;
		return false;
	}

	bool Color::IsValid() const
	{
		if (!Mathf::IsFinite(r))
			return false;
		if (!Mathf::IsFinite(g))
			return false;
		if (!Mathf::IsFinite(b))
			return false;
		if (!Mathf::IsFinite(a))
			return false;
		return true;
	}

	void Color::operator=(const ColorLinear& cc)
	{
		*this = cc.ToLinearFloat();
	}

	void Color::operator=(const ColorGamma& cc)
	{
		*this = cc.ToGammaFloat();
	}

	void Color::operator+=(const Color& rhs)
	{
		r += rhs.r;
		g += rhs.g;
		b += rhs.b;
		a += rhs.a;
	}

	void Color::operator-=(const Color& rhs)
	{
		r -= rhs.r;
		g -= rhs.g;
		b -= rhs.b;
		a -= rhs.a;
	}

	void Color::operator*=(const Color& rhs)
	{
		r *= rhs.r;
		g *= rhs.g;
		b *= rhs.b;
		a *= rhs.a;
	}

	void Color::operator*=(float fScalar)
	{
		r *= fScalar;
		g *= fScalar;
		b *= fScalar;
		a *= fScalar;
	}

	void Color::operator/=(float fScalar)
	{
		float f_inv = 1.0f / fScalar;
		r *= f_inv;
		g *= f_inv;
		b *= f_inv;
		a *= f_inv;
	}


	void Color::operator*=(const Mat4& rhs)
	{
		Vec3 v(r, g, b);
		Vec3 tmp = Vec3::zero();

		tmp.x = v.x * rhs.m[0][0] + v.y * rhs.m[1][0] + v.z * rhs.m[2][0] + rhs.m[3][0];
		tmp.y = v.x * rhs.m[0][1] + v.y * rhs.m[1][1] + v.z * rhs.m[2][1] + rhs.m[3][1];
		tmp.z = v.x * rhs.m[0][2] + v.y * rhs.m[1][2] + v.z * rhs.m[2][2] + rhs.m[3][2];
		
		r = tmp.x;
		g = tmp.y;
		b = tmp.z;
	}

	float& Color::operator[](int index)
	{
		switch (index)
		{
		case 0: return r;
		case 1: return g;
		case 2: return b;
		case 3: return a;
		default:
			throw std::out_of_range("Color::operator[] index out of range");
		}
	}

	float const& Color::operator[](int index) const
	{
		switch (index)
		{
		case 0: return r;
		case 1: return g;
		case 2: return b;
		case 3: return a;
		default:
			throw std::out_of_range("Color::operator[] index out of range");
		}
	}

	bool Color::IsIdenticalRGB(const Color& rhs) const
	{
		return r == rhs.r && g == rhs.g && b == rhs.b;
	}

	bool Color::IsIdenticalRGBA(const Color& rhs) const
	{
		return r == rhs.r && g == rhs.g && b == rhs.b && a == rhs.a;
	}

	bool Color::IsEqualRGB(const Color& rhs, float fEpsilon) const
	{
		return (Mathf::IsEqual(r, rhs.r, fEpsilon) && Mathf::IsEqual(g, rhs.g, fEpsilon) && Mathf::IsEqual(b, rhs.b, fEpsilon));
	}

	bool Color::IsEqualRGBA(const Color& rhs, float fEpsilon) const
	{
		return (Mathf::IsEqual(r, rhs.r, fEpsilon) && Mathf::IsEqual(g, rhs.g, fEpsilon) && Mathf::IsEqual(b, rhs.b, fEpsilon) && Mathf::IsEqual(a, rhs.a, fEpsilon));
	}

	Color Color::WithAlpha(float fAlpha) const
	{
		return Color(r, g, b, fAlpha);
	}

	const Color operator+(const Color& c1, const Color& c2)
	{
		return Color(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b, c1.a + c2.a);
	}

	const Color operator-(const Color& c1, const Color& c2)
	{
		return Color(c1.r - c2.r, c1.g - c2.g, c1.b - c2.b, c1.a - c2.a);
	}

	const Color operator*(const Color& c1, const Color& c2)
	{
		return Color(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b, c1.a * c2.a);
	}
	
	const Color operator*(const Color& c1, float fScalar)
	{
		return Color(c1.r * fScalar, c1.g * fScalar, c1.b * fScalar, c1.a * fScalar);
	}
	
	const Color operator*(float fScalar, const Color& c1)
	{
		return Color(c1.r * fScalar, c1.g * fScalar, c1.b * fScalar, c1.a * fScalar);
	}

	const Color operator/(const Color& c1, float fScalar)
	{
		float f_inv = 1.0f / fScalar;
		return Color(c1.r * f_inv, c1.g * f_inv, c1.b * f_inv, c1.a * f_inv);
	}

	const Color operator*(const Mat4& lhs, const Color& rhs)
	{
		Color r = rhs;
		r *= lhs;
		return r;
	}

	bool operator==(const Color& c1, const Color& c2)
	{
		return c1.IsIdenticalRGBA(c2);
	}

	bool operator!=(const Color& c1, const Color& c2)
	{
		return !c1.IsIdenticalRGBA(c2);
	}

	bool operator<(const Color& c1, const Color& c2)
	{
		if (c1.r < c2.r)
			return true;
		if (c1.r > c2.r)
			return false;
		if (c1.g < c2.g)
			return true;
		if (c1.g > c2.g)
			return false;
		if (c1.b < c2.b)
			return true;
		if (c1.b > c2.b)
			return false;

		return (c1.a < c2.a);
	}

}
