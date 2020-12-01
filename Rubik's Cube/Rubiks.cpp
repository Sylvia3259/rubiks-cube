#include "Rubiks.h"

Rubiks::Rubiks() {
	const double coord[3] = { -2, 0, +2 };
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			for (int k = 0; k < 3; ++k)
				cubes[i][j][k] = Cube(coord[i], coord[j], coord[k]);

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			for (int k = 0; k < 2; ++k)
				cubes[0][i][j].polygons[k].color = FG_DARK_RED | BG_DARK_YELLOW;

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			for (int k = 2; k < 4; ++k)
				cubes[2][i][j].polygons[k].color = FG_RED | BG_DARK_RED;

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			for (int k = 4; k < 6; ++k)
				cubes[i][0][j].polygons[k].color = FG_BLUE | BG_BLUE;

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			for (int k = 6; k < 8; ++k)
				cubes[i][2][j].polygons[k].color = FG_GREEN | BG_GREEN;

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			for (int k = 8; k < 10; ++k)
				cubes[i][j][0].polygons[k].color = FG_WHITE | BG_WHITE;

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			for (int k = 10; k < 12; ++k)
				cubes[i][j][2].polygons[k].color = FG_YELLOW | BG_DARK_YELLOW;
}