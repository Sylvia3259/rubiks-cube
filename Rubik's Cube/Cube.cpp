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