#pragma once

#include <windows.h>
#define _USE_MATH_DEFINES
#include <math.h>

#define D2R (M_PI/180)

struct Point : public POINT
{
	Point();
	Point(const LONG& _x, const LONG& _y);

	Point operator + (const Point& o) const;
	Point operator - (const Point& o) const;
	LONG operator ^ (const Point& o) const;

	bool operator != (const Point& o) const;

	Point ToClient(HWND hWnd) const;
	Point ToScreen(HWND hWnd) const;
};

struct Size : public SIZE
{
	Size();
	Size(const LONG& _cx, const LONG& _cy);
};

struct Rect : public RECT
{
	Rect();
	Rect(const LONG& l, const LONG& t, const LONG& r, const LONG& b);
   Rect(const Point& lt, const Point& rb);
	Rect(const Point& pt, const Size& cs);

	Point center() const;

	LONG width() const;
	LONG height() const;
   float radius() const;
};

struct Vector 
{
	float x, y;

	Vector();
	Vector(const float& _x, const float& _y);
	Vector(const Point& pt);

	float size() const;
	Vector normalize() const;
	Vector projection(const Vector& on) const;
	Vector rejection(const Vector& from) const;


	Vector operator + (const Vector& o) const;
	Vector operator - (const Vector& o) const;
	template<typename T>
	Vector operator / (const T& scalar) const
	{
		return Vector(x/scalar, y/scalar);
	}
	template<typename T>
	friend Vector operator * (const Vector& v, const T& scalar)
	{
		return Vector(v.x*scalar, v.y*scalar);
	}
	template<typename T>
	friend Vector operator * (const T& scalar, const Vector& v)
	{
		return Vector(v.x*scalar, v.y*scalar);
	}
	float operator * (const Vector& o) const;
	operator Point ();

	bool operator == (const Vector& o) const;

};
