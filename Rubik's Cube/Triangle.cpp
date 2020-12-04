#include "Triangle.h"

Triangle::Triangle() {
	color = 0;
}

Triangle::Triangle(const Vector& v1, const Vector& v2, const Vector& v3) {
	color = 0;
	points = { v1, v2, v3 };
}

void Triangle::Scale(double x, double y, double z) {
	for (auto& point : points)
		point.Scale(x, y, z);
}

void Triangle::Rotate(double x, double y, double z) {
	for (auto& point : points)
		point.Rotate(x, y, z);
}

void Triangle::Translate(double x, double y, double z) {
	for (auto& point : points)
		point.Translate(x, y, z);
}

void Triangle::Project(double near, double far, double fov, double aspect) {
	for (auto& point : points)
		point.Project(near, far, fov, aspect);
}