#include "Color8UNorm.h"

namespace TDS
{
	ColorBase::ColorBase(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
	uint8_t& ColorBase::operator[](int index)
	{
		return (&r)[index];
	}
	const uint8_t& ColorBase::operator[](int index) const
	{
		return (&r)[index];
	}
	ColorLinear::ColorLinear(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
		: ColorBase(r, g, b, a)
	{	
	}
	ColorLinear::ColorLinear(const Color& color)
	{
		*this = color;
	}
	void ColorLinear::operator=(const Color& color)
	{
		r = Mathf::ColorFloatToByte(color.r);
		g = Mathf::ColorFloatToByte(color.g);
		b = Mathf::ColorFloatToByte(color.b);
		a = Mathf::ColorFloatToByte(color.a);
	}
	Color ColorLinear::ToLinearFloat() const
	{
		return Color(Mathf::ColorByteToFloat(r), Mathf::ColorByteToFloat(g), Mathf::ColorByteToFloat(b), Mathf::ColorByteToFloat(a));
	}

	ColorGamma::ColorGamma(uint8_t uiGammaRed, uint8_t uiGammaGreen, uint8_t uiGammaBlue, uint8_t uiGammaAlpha)
		: ColorBase(uiGammaRed, uiGammaGreen, uiGammaBlue, uiGammaAlpha)
	{
	}

	ColorGamma::ColorGamma(const Color& color)
	{
		*this = color;
	}

	void ColorGamma::operator=(const Color& color)
	{
		const Vec3 gamma = Color::LinearToGamma(Vec3(color.r, color.g, color.b));
		r = Mathf::ColorFloatToByte(gamma.x);
		g = Mathf::ColorFloatToByte(gamma.y);
		b = Mathf::ColorFloatToByte(gamma.z);
		a = Mathf::ColorFloatToByte(color.a);
	}

	Color ColorGamma::ToGammaFloat() const
	{
		Vec3 gamma;
		gamma.x = Mathf::ColorByteToFloat(r);
		gamma.y = Mathf::ColorByteToFloat(g);
		gamma.z = Mathf::ColorByteToFloat(b);
		
		const Vec3 linear = Color::GammaToLinear(gamma);
		return Color(linear.x, linear.y, linear.z, Mathf::ColorByteToFloat(a));
	}

}
