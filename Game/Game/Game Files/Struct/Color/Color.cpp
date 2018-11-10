#include "Color.h"


Color Color::operator+(const Color &other)const
{
	return Color(R + other.R, G + other.G, B + other.B, A + other.A);
}

Color Color::operator-(const Color &other)const
{
	return Color(R - other.R, G - other.G, B - other.B, A - other.A);
}


Color& Color::operator+=(const Color &other)
{
	R += other.R;
	G += other.G;
	B += other.B;
	A += other.A;
	return *this;
}

Color& Color::operator-=(const Color &other)
{
	R -= other.R;
	G -= other.G;
	B -= other.B;
	A -= other.A;
	return *this;
}


Color& Color::operator=(const Color &other)
{
	R = other.R;
	G = other.G;
	B = other.B;
	A = other.A;
	return *this;
}

float Color::operator[](const int p_index)const
{
	return  *(((float*)(this)) + p_index);
}


const Color Color::Red(255, 0, 0, 255);
const Color Color::Green(0, 255, 0, 255);
const Color Color::Blue(0, 0, 255, 255);
const Color Color::Black(0, 0, 0, 255);
const Color Color::White(255, 255, 255, 255);