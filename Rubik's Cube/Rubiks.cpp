#include "Rubiks.h"

Rubiks::Rubiks() {
	const double coord[3] = { -2, 0, +2 };
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			for (int k = 0; k < 3; ++k) {
				const double x = coord[i], y = coord[j], z = coord[k];

				cubeCenters[i][j][k] = Vector(x, y, z);

				cubes[i][j][k][0] = Triangle(Vector(x-1, y-1, z+1), Vector(x-1, y+1, z+1), Vector(x-1, y+1, z-1));
				cubes[i][j][k][1] = Triangle(Vector(x-1, y-1, z+1), Vector(x-1, y+1, z-1), Vector(x-1, y-1, z-1));

				cubes[i][j][k][2] = Triangle(Vector(x+1, y-1, z-1), Vector(x+1, y+1, z-1), Vector(x+1, y+1, z+1));
				cubes[i][j][k][3] = Triangle(Vector(x+1, y-1, z-1), Vector(x+1, y+1, z+1), Vector(x+1, y-1, z+1));

				cubes[i][j][k][4] = Triangle(Vector(x+1, y-1, z+1), Vector(x-1, y-1, z+1), Vector(x-1, y-1, z-1));
				cubes[i][j][k][5] = Triangle(Vector(x+1, y-1, z+1), Vector(x-1, y-1, z-1), Vector(x+1, y-1, z-1));

				cubes[i][j][k][6] = Triangle(Vector(x-1, y+1, z-1), Vector(x-1, y+1, z+1), Vector(x+1, y+1, z+1));
				cubes[i][j][k][7] = Triangle(Vector(x-1, y+1, z-1), Vector(x+1, y+1, z+1), Vector(x+1, y+1, z-1));

				cubes[i][j][k][8] = Triangle(Vector(x-1, y-1, z-1), Vector(x-1, y+1, z-1), Vector(x+1, y+1, z-1));
				cubes[i][j][k][9] = Triangle(Vector(x-1, y-1, z-1), Vector(x+1, y+1, z-1), Vector(x+1, y-1, z-1));

				cubes[i][j][k][10] = Triangle(Vector(x+1, y-1, z+1), Vector(x+1, y+1, z+1), Vector(x-1, y+1, z+1));
				cubes[i][j][k][11] = Triangle(Vector(x+1, y-1, z+1), Vector(x-1, y+1, z+1), Vector(x-1, y-1, z+1));
			}
		}
	}

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			cubes[0][i][j][0].color = FG_DARK_RED | BG_DARK_YELLOW;
			cubes[0][i][j][1].color = FG_DARK_RED | BG_DARK_YELLOW;
		}
	}

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			cubes[2][i][j][2].color = FG_RED | BG_DARK_RED;
			cubes[2][i][j][3].color = FG_RED | BG_DARK_RED;
		}
	}

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			cubes[i][0][j][4].color = FG_BLUE | BG_BLUE;
			cubes[i][0][j][5].color = FG_BLUE | BG_BLUE;
		}
	}

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			cubes[i][2][j][6].color = FG_GREEN | BG_GREEN;
			cubes[i][2][j][7].color = FG_GREEN | BG_GREEN;
		}
	}

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			cubes[i][j][0][8].color = FG_WHITE | BG_WHITE;
			cubes[i][j][0][9].color = FG_WHITE | BG_WHITE;
		}
	}

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			cubes[i][j][2][10].color = FG_YELLOW | BG_DARK_YELLOW;
			cubes[i][j][2][11].color = FG_YELLOW | BG_DARK_YELLOW;
		}
	}
}