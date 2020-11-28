#pragma once
#include "Vector.h"

class Triangle {
public:
	Vector point[3];

	Triangle();
	Triangle(const Triangle& obj);
	Triangle(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3);

	void Translate(double x, double y, double z);
	void Rotate(double x, double y, double z);
	void Project(double near, double far, double fov, double aspect);
};