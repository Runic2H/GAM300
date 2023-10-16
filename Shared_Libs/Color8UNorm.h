#ifndef COLOUR8UNORM_H
#define COLOUR8UNORM_H

#include "Color.h"

namespace TDS
{
class ColorBase
{
public:
	// Constructor
	ColorBase() = default;
	ColorBase(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
	
	uint8_t& operator[](int index);
	const uint8_t& operator[](int index) const;

	// Data
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
};

class ColorLinear : public ColorBase
{
public:
	// Constructor
	ColorLinear() = default;
	ColorLinear(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
	ColorLinear(const Color& color);

	void operator=(const Color& color);

	Color ToLinearFloat() const;
};

class ColorGamma : public ColorBase
{
public:
	// Constructor
	ColorGamma() = default;
	ColorGamma(uint8_t uiGammaRed, uint8_t uiGammaGreen, uint8_t uiGammaBlue, uint8_t uiGammaAlpha = 255);
	ColorGamma(const Color& color);

	void operator=(const Color& color);

	Color ToGammaFloat() const;
};


} 

#endif // !COLOUR8UNORM_H