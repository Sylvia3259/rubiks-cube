#pragma once
#include <math.h>

class Vector {
public:
	double x;
	double y;
	double z;

	Vector();
	Vector(double x, double y, double z);

	double Magnitude();
	void Normalize();
	double Dot(Vector v);
	Vector Cross(Vector v);
	void Scale(double x, double y, double z);
	void Rotate(double x, double y, double z);
	void Translate(double x, double y, double z);
	void Project(double near, double far, double fov, double aspect);

	Vector operator+(const Vector& v) const;
	Vector operator-(const Vector& v) const;
	Vector operator+() const;
	Vector operator-() const;
	Vector operator*(const double k) const;
	Vector& operator+=(const Vector& v);
	Vector& operator-=(const Vector& v);
	Vector& operator*=(const double k);
};

Vector operator*(const double k, const Vector& v);