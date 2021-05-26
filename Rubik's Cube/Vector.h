#pragma once
#include <cmath>

class Vector {
public:
	double x, y, z;

	Vector();
	Vector(double x, double y, double z);

	double Magnitude();
	void Normalize();
	double Dot(const Vector& v);
	Vector Cross(const Vector& v);
	void Scale(double x, double y, double z);
	void Rotate(double x, double y, double z);
	void Translate(double x, double y, double z);
	void Project(double near, double far, double fov, double aspect);

	Vector operator+(const Vector& v) const;
	Vector operator-(const Vector& v) const;
	Vector operator+() const;
	Vector operator-() const;
	Vector operator*(double k) const;
	friend Vector operator*(double k, const Vector& v);
};