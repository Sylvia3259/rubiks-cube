#pragma once
#include <math.h>

class Vector {
public:
	double x;
	double y;
	double z;

	Vector();
	Vector(const Vector& obj);
	Vector(double x, double y, double z);

	void Normalize();
	void Translate(double x, double y, double z);
	void Rotate(double x, double y, double z);
	void Project(double near, double far, double fov, double aspect);
};