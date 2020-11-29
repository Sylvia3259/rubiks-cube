#include "Triangle.h"

Triangle::Triangle() {
	color = 0x0000;
}

Triangle::Triangle(const Vector& v1, const Vector& v2, const Vector& v3) {
	color = 0x0000;

	points[0] = v1;
	points[1] = v2;
	points[2] = v3;
}

void Triangle::Scale(double x, double y, double z) {
	for (auto& p : points)
		p.Scale(x, y, z);
}

void Triangle::Rotate(double x, double y, double z) {
	for (auto& p : points)
		p.Rotate(x, y, z);
}

void Triangle::Translate(double x, double y, double z) {
	for (auto& p : points)
		p.Translate(x, y, z);
}

void Triangle::Project(double near, double far, double fov, double aspect) {
	for (auto& p : points)
		p.Project(near, far, fov, aspect);
}