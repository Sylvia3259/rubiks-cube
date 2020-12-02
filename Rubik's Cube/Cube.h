#pragma once
#include "Triangle.h"

class Cube {
public:
	std::vector<Triangle> polygons;

	Cube();
	Cube(double x, double y, double z);

	void Scale(double x, double y, double z);
	void Rotate(double x, double y, double z);
	void Translate(double x, double y, double z);
};