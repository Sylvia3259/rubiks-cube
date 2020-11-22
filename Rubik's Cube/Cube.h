#pragma once
#include "Vector.h"

class Cube {
private:
	Vector vertex[2][2][2];
public:
	Cube();
	Cube(double x, double y, double z);
	void Rotate(double x, double y, double z);
};