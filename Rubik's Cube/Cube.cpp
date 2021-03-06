#include "Cube.h"

Cube::Cube() {
	polygons = {
		Triangle(Vector(-1, -1, +1), Vector(-1, +1, +1), Vector(-1, +1, -1)),
		Triangle(Vector(-1, -1, +1), Vector(-1, +1, -1), Vector(-1, -1, -1)),

		Triangle(Vector(+1, -1, -1), Vector(+1, +1, -1), Vector(+1, +1, +1)),
		Triangle(Vector(+1, -1, -1), Vector(+1, +1, +1), Vector(+1, -1, +1)),

		Triangle(Vector(+1, -1, +1), Vector(-1, -1, +1), Vector(-1, -1, -1)),
		Triangle(Vector(+1, -1, +1), Vector(-1, -1, -1), Vector(+1, -1, -1)),

		Triangle(Vector(-1, +1, -1), Vector(-1, +1, +1), Vector(+1, +1, +1)),
		Triangle(Vector(-1, +1, -1), Vector(+1, +1, +1), Vector(+1, +1, -1)),

		Triangle(Vector(-1, -1, -1), Vector(-1, +1, -1), Vector(+1, +1, -1)),
		Triangle(Vector(-1, -1, -1), Vector(+1, +1, -1), Vector(+1, -1, -1)),

		Triangle(Vector(+1, -1, +1), Vector(+1, +1, +1), Vector(-1, +1, +1)),
		Triangle(Vector(+1, -1, +1), Vector(-1, +1, +1), Vector(-1, -1, +1)),
	};
}

Cube::Cube(double x, double y, double z) {
	polygons = {
		Triangle(Vector(x-1, y-1, z+1), Vector(x-1, y+1, z+1), Vector(x-1, y+1, z-1)),
		Triangle(Vector(x-1, y-1, z+1), Vector(x-1, y+1, z-1), Vector(x-1, y-1, z-1)),

		Triangle(Vector(x+1, y-1, z-1), Vector(x+1, y+1, z-1), Vector(x+1, y+1, z+1)),
		Triangle(Vector(x+1, y-1, z-1), Vector(x+1, y+1, z+1), Vector(x+1, y-1, z+1)),

		Triangle(Vector(x+1, y-1, z+1), Vector(x-1, y-1, z+1), Vector(x-1, y-1, z-1)),
		Triangle(Vector(x+1, y-1, z+1), Vector(x-1, y-1, z-1), Vector(x+1, y-1, z-1)),

		Triangle(Vector(x-1, y+1, z-1), Vector(x-1, y+1, z+1), Vector(x+1, y+1, z+1)),
		Triangle(Vector(x-1, y+1, z-1), Vector(x+1, y+1, z+1), Vector(x+1, y+1, z-1)),

		Triangle(Vector(x-1, y-1, z-1), Vector(x-1, y+1, z-1), Vector(x+1, y+1, z-1)),
		Triangle(Vector(x-1, y-1, z-1), Vector(x+1, y+1, z-1), Vector(x+1, y-1, z-1)),

		Triangle(Vector(x+1, y-1, z+1), Vector(x+1, y+1, z+1), Vector(x-1, y+1, z+1)),
		Triangle(Vector(x+1, y-1, z+1), Vector(x-1, y+1, z+1), Vector(x-1, y-1, z+1)),
	};
}

void Cube::Scale(double x, double y, double z) {
	for (auto& polygon : polygons)
		polygon.Scale(x, y, z);
}

void Cube::Rotate(double x, double y, double z) {
	for (auto& polygon : polygons)
		polygon.Rotate(x, y, z);
}

void Cube::Translate(double x, double y, double z) {
	for (auto& polygon : polygons)
		polygon.Translate(x, y, z);
}