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

void Rubiks::Control(std::string command) {
	controlQueue.push(command);
}

void Rubiks::Update(double deltaTime) {
	static double theta = 0;

	if (!controlQueue.empty()) {
		std::string command = controlQueue.front();

		char symbol = command[0];
		int index = command[1] - '0';
		char direction = command[2];

		double rotation = MIN(deltaTime * controlSpeed, 90 - ABS(theta));
		if (direction == '-') rotation = -rotation;

		if (symbol == 'i')
			for (int i = 0; i < 3; ++i)
				for (int j = 0; j < 3; ++j)
					cubes[index][i][j].Rotate(rotation, 0, 0);
		else if (symbol == 'j')
			for (int i = 0; i < 3; ++i)
				for (int j = 0; j < 3; ++j)
					cubes[i][index][j].Rotate(0, rotation, 0);
		else if (symbol == 'k')
			for (int i = 0; i < 3; ++i)
				for (int j = 0; j < 3; ++j)
					cubes[i][j][index].Rotate(0, 0, rotation);

		theta += rotation;
		if (ABS(theta) >= 90) {
			Rubiks tempCube = *this;
			if (symbol == 'i') {
				if (direction == '+')
					for (int i = 0; i < 3; ++i)
						for (int j = 0; j < 3; ++j)
							cubes[index][i][j] = tempCube.cubes[index][j][2 - i];
				else if (direction == '-')
					for (int i = 0; i < 3; ++i)
						for (int j = 0; j < 3; ++j)
							cubes[index][i][j] = tempCube.cubes[index][2 - j][i];
			}
			else if (symbol == 'j') {
				if (direction == '+')
					for (int i = 0; i < 3; ++i)
						for (int j = 0; j < 3; ++j)
							cubes[i][index][j] = tempCube.cubes[2 - j][index][i];
				else if (direction == '-')
					for (int i = 0; i < 3; ++i)
						for (int j = 0; j < 3; ++j)
							cubes[i][index][j] = tempCube.cubes[j][index][2 - i];
			}
			else if (symbol == 'k') {
				if (direction == '+')
					for (int i = 0; i < 3; ++i)
						for (int j = 0; j < 3; ++j)
							cubes[i][j][index] = tempCube.cubes[j][2 - i][index];
				else if (direction == '-')
					for (int i = 0; i < 3; ++i)
						for (int j = 0; j < 3; ++j)
							cubes[i][j][index] = tempCube.cubes[2 - j][i][index];
			}

			controlQueue.pop();
			theta = 0;
		}
	}
}

void Rubiks::Scale(double x, double y, double z) {
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			for (int k = 0; k < 3; ++k)
				cubes[i][j][k].Scale(x, y, z);
}

void Rubiks::Rotate(double x, double y, double z) {
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			for (int k = 0; k < 3; ++k)
				cubes[i][j][k].Rotate(x, y, z);
}

void Rubiks::Translate(double x, double y, double z) {
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			for (int k = 0; k < 3; ++k)
				cubes[i][j][k].Translate(x, y, z);
}