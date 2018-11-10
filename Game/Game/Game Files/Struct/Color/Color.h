#pragma once

struct Color
{
	Color(float r = 0, float g = 0, float b = 0, float a = 0) : R(r), G(g), B(b), A(a) {}
	Color(const Color &other) : R(other.R), G(other.G), B(other.B), A(other.A) {}

	Color operator+(const Color &other)const;
	Color operator-(const Color &other)const;

	Color& operator+=(const Color &other);
	Color& operator-=(const Color &other);

	Color& operator=(const Color &other);

	bool operator==(const Color &other)const { return R == other.R && G == other.G && B == other.B && A == other.A; }
	bool operator!=(const Color &other)const { return R != other.R || G != other.G || B != other.B || A != other.A; }

	float operator[](const int index)const;

	float R;
	float G;
	float B;
	float A;

	static const Color Red;
	static const Color Green;
	static const Color Blue;
	static const Color Black;
	static const Color White;
};