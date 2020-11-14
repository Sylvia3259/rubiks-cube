#pragma once
#include <cmath>

class Point {
private:
	double x;
	double y;
	double z;
public:
	Point();
	Point(double x, double y, double z);
	void Rotate(double x, double y, double z);
};