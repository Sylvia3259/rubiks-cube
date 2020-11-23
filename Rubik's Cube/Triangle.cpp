#include "Triangle.h"

Triangle::Triangle() {}

Triangle::Triangle(const Triangle& obj) {
	for (int i = 0; i < 3; ++i)
		point[i] = Vector(obj.point[i]);
}

Triangle::Triangle(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3) {
	point[0] = Vector(x1, y1, z1);
	point[1] = Vector(x2, y2, z2);
	point[2] = Vector(x3, y3, z3);
}

void Triangle::Translate(double x, double y, double z) {
	for (auto& p : point)
		p.Translate(x, y, z);
}

void Triangle::Rotate(double x, double y, double z) {
	for (auto& p : point)
		p.Rotate(x, y, z);
}

void Triangle::Project(double near, double far, double fov, double aspect) {
	for (auto& p : point)
		p.Project(near, far, fov, aspect);
}