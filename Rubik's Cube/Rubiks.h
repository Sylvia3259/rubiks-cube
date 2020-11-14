#pragma once
#include "Cube.h"

class Rubiks {
private:
	Cube cube[3][3][3];
public:
	Rubiks();
	void Rotate(int command);
};