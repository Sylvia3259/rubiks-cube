#pragma once
#include "Triangle.h"
#include "constants.h"

class Rubiks {
public:
	Triangle cubes[3][3][3][12];
	Vector cubeCenters[3][3][3];

	Rubiks();
};