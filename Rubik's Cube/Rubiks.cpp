#include "Rubiks.h"

Rubiks::Rubiks() {
	const double coord[3] = { -1, 0, 1 };
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			for (int k = 0; k < 3; ++k)
				cube[i][j][k] = Cube(coord[i], coord[j], coord[k]);
}

void Rubiks::Rotate(int command) {

}
