#include "Cube.h"

Cube::Cube() {
	const double coord[2] = { -1, 1 };
	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 2; ++j)
			for (int k = 0; k < 2; ++k)
				vertex[i][j][k] = Point(coord[i], coord[j], coord[k]);
}

Cube::Cube(double x, double y, double z) {
	const double coord[2] = { -1, 1 };
	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 2; ++j)
			for (int k = 0; k < 2; ++k)
				vertex[i][j][k] = Point(x + coord[i], y + coord[j], z + coord[k]);
}

void Cube::Rotate(double x, double y, double z) {
	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 2; ++j)
			for (int k = 0; k < 2; ++k)
				vertex[i][j][k].Rotate(x, y, z);
}