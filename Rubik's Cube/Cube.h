#pragma once
#include "Point.h"

class Cube {
private:
	Point vertex[2][2][2];
public:
	Cube();
	Cube(double x, double y, double z);
	void Rotate(double x, double y, double z);
};