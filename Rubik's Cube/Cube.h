#pragma once
#include "Triangle.h"

class Cube {
public:
	std::vector<Triangle> polygons;

	Cube();
	Cube(double x, double y, double z);
};