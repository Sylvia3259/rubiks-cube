#include "Vector.h"

Vector::Vector() : x(0), y(0), z(0) {}

Vector::Vector(double x, double y, double z) : x(x), y(y), z(z) {}

double Vector::Magnitude() {
	return sqrt(x*x + y*y + z*z);
}

void Vector::Normalize() {
	double length = sqrt(x*x + y*y + z*z);

	x /= length;
	y /= length;
	z /= length;
}

double Vector::Dot(const Vector& v) {
	return x*v.x + y*v.y + z*v.z;
}

Vector Vector::Cross(const Vector& v) {
	return Vector(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
}

void Vector::Scale(double x, double y, double z) {
	this->x *= x;
	this->y *= y;
	this->z *= z;
}

void Vector::Rotate(double x, double y, double z) {
	x *= 3.14159 / 180;
	y *= 3.14159 / 180;
	z *= 3.14159 / 180;

	double tx, ty, tz;

	tx = this->x * (cos(y) * cos(z))
		+ this->y * (-cos(x) * sin(z) + sin(x) * sin(y) * cos(z))
		+ this->z * (sin(x) * sin(z) + cos(x) * sin(y) * cos(z));
	ty = this->x * (cos(y) * sin(z))
		+ this->y * (cos(x) * cos(z) + sin(x) * sin(y) * sin(z))
		+ this->z * (-sin(x) * cos(z) + cos(x) * sin(y) * sin(z));
	tz = this->x * (-sin(y))
		+ this->y * (sin(x) * cos(y))
		+ this->z * (cos(x) * cos(y));

	this->x = tx;
	this->y = ty;
	this->z = tz;
}

void Vector::Translate(double x, double y, double z) {
	this->x += x;
	this->y += y;
	this->z += z;
}

void Vector::Project(double near, double far, double fov, double aspect) {
	fov *= 3.14159 / 180;

	double tx, ty, tz;

	tx = (x * ((1 / tan(fov * 0.5)) / aspect)) / z;
	ty = (y * (1 / tan(fov * 0.5))) / z;
	tz = (z * (far / (far - near)) + (-near * far / (far - near))) / z;

	x = tx;
	y = ty;
	z = tz;
}

Vector Vector::operator+(const Vector& v) const {
	return Vector(x+v.x, y+v.y, z+v.z);
}

Vector Vector::operator-(const Vector& v) const {
	return Vector(x-v.x, y-v.y, z-v.z);
}

Vector Vector::operator+() const {
	return Vector(+x, +y, +z);
}

Vector Vector::operator-() const {
	return Vector(-x, -y, -z);
}

Vector Vector::operator*(double k) const {
	return Vector(k*x, k*y, k*z);
}

Vector operator*(double k, const Vector& v) {
	return Vector(k*v.x, k*v.y, k*v.z);
}