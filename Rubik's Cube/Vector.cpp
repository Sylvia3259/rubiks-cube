#include "Vector.h"

Vector::Vector() {
	x = 0, y = 0, z = 0;
}

Vector::Vector(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

void Vector::Normalize() {
	double length = sqrt(x*x + y*y + z*z);

	x /= length; 
	y /= length; 
	z /= length;
}

void Vector::Translate(double x, double y, double z) {
	this->x += x;
	this->y += y;
	this->z += z;
}

void Vector::Rotate(double x, double y, double z) {
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

void Vector::Project(double near, double far, double fov, double aspect) {
	fov *= 3.14159 / 180.0;

	double tx, ty, tz;

	tx = x * (1.f / (aspect * tanf(fov * 0.5f)));
	ty = y * (1.f / tanf(fov * 0.5f));
	tz = z * (far / (far - near)) + ((-far * near) / (far - near));

	if (z != 0) {
		tx /= z; 
		ty /= z; 
		tz /= z;
	}

	x = tx;
	y = ty;
	z = tz;
}