#pragma once
#include <queue>
#include <string>
#include "Cube.h"
#include "macros.h"
#include "constants.h"

class Rubiks {
private:
	std::queue<std::string> controlQueue;

public:
	Cube cubes[3][3][3];

	Rubiks();

	void Control(std::string command);
	void Update(double deltaTime);
	void Scale(double x, double y, double z);
	void Rotate(double x, double y, double z);
	void Translate(double x, double y, double z);
};