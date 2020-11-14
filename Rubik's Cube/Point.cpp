#include "Point.h"

Point::Point() {
	x = 0, y = 0, z = 0;
}

Point::Point(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

void Point::Rotate(double x, double y, double z) {
	double tx, ty, tz;

	tx  = this->x * (cos(y) * cos(z))
		+ this->y * (-cos(x) * sin(z) + sin(x) * sin(y) * cos(z))
		+ this->z * (sin(x) * sin(z) + cos(x) * sin(y) * cos(z));
	ty  = this->x * (cos(y) * sin(z))
		+ this->y * (cos(x) * cos(z) + sin(x) * sin(y) * sin(z))
		+ this->z * (-sin(x) * cos(z) + cos(x) * sin(y) * sin(z));
	tz  = this->x * (-sin(y)) 
		+ this->y * (sin(x) * cos(y)) 
		+ this->z * (cos(x) * cos(y));

	this->x = tx;
	this->y = ty;
	this->z = tz;
}