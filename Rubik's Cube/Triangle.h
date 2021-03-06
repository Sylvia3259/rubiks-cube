#pragma once
#include <vector>
#include "Vector.h"

class Triangle {
public:
	short color;
	std::vector<Vector> points;

	Triangle();
	Triangle(const Vector& v1, const Vector& v2, const Vector& v3);
	
	void Scale(double x, double y, double z);
	void Rotate(double x, double y, double z);
	void Translate(double x, double y, double z);
	void Project(double near, double far, double fov, double aspect);
};