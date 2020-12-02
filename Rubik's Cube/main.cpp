#include <algorithm>
#include "Rubiks.h"
#include "Engine.h"
using namespace std;

class RubiksEngine : public Engine {
private:
	double theta;
	Rubiks rubiksCube;

public:
	RubiksEngine(short width, short height) : Engine(width, height) {
		theta = 0;
	}

	void OnCreate() override {
		rubiksCube.Control("k2+");
		rubiksCube.Control("i2+");
		rubiksCube.Control("i2-");
		rubiksCube.Control("j1-");
		rubiksCube.Control("k0-");
		rubiksCube.Control("k1-");
		rubiksCube.Control("k0-");
		rubiksCube.Control("i2+");
		rubiksCube.Control("k1-");
		rubiksCube.Control("i2+");
		rubiksCube.Control("j2+");
		rubiksCube.Control("i2+");
		rubiksCube.Control("k0-");
		rubiksCube.Control("k0+");
		rubiksCube.Control("j0+");
		rubiksCube.Control("k2+");
		rubiksCube.Control("i0+");
		rubiksCube.Control("k0-");
		rubiksCube.Control("i0-");
		rubiksCube.Control("j1+");
		rubiksCube.Control("i1-");
		rubiksCube.Control("j2+");
		rubiksCube.Control("i2-");
		rubiksCube.Control("k1+");
		rubiksCube.Control("i0-");
		rubiksCube.Control("k0+");
		rubiksCube.Control("k0+");
		rubiksCube.Control("j2+");
		rubiksCube.Control("i1-");
		rubiksCube.Control("i2-");
		rubiksCube.Control("k0-");
		rubiksCube.Control("j2-");
		rubiksCube.Control("j1+");
		rubiksCube.Control("j2+");
		rubiksCube.Control("k1+");
		rubiksCube.Control("i1+");
		rubiksCube.Control("j0-");
		rubiksCube.Control("j2-");
		rubiksCube.Control("i2+");
		rubiksCube.Control("k2+");
		rubiksCube.Control("k0-");
		rubiksCube.Control("j1+");
		rubiksCube.Control("j2-");
		rubiksCube.Control("k1-");
		rubiksCube.Control("i0-");
		rubiksCube.Control("k2+");
		rubiksCube.Control("i2-");
		rubiksCube.Control("k0-");
		rubiksCube.Control("k0+");
		rubiksCube.Control("i0+");
	}

	void OnUpdate(double deltaTime) override {
		theta += deltaTime * 90; 

		rubiksCube.Update(deltaTime);

		Rubiks tempCube = rubiksCube;
		tempCube.Rotate(theta * 1.0, theta * 0.5, theta * 0.75);
		tempCube.Translate(0, 0, 10);

		vector<Cube*> cubes;
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				for (int k = 0; k < 3; ++k)
					cubes.push_back(&tempCube.cubes[i][j][k]);

		vector<Triangle> triangles;
		for (Cube* const cube : cubes) {
			for (const Triangle& triangle : cube->polygons) {
				Vector line1, line2, normal;
				line1 = triangle.points[1] - triangle.points[0];
				line2 = triangle.points[2] - triangle.points[0];
				normal = line1.Cross(line2);
				normal.Normalize();

				if (normal.Dot(triangle.points[0]) < 0)
					triangles.push_back(triangle);
			}
		}

		sort(triangles.begin(), triangles.end(), 
			[](const Triangle& lhs, const Triangle& rhs) {
				return lhs.points[0].z + lhs.points[1].z + lhs.points[2].z > 
					rhs.points[0].z + rhs.points[1].z + rhs.points[2].z;
			});

		for (Triangle& triangle : triangles) {
			triangle.Project(0.1, 1000, 90, (double)GetScreenWidth() / GetScreenHeight());

			triangle.Translate(1, 1, 0);
			triangle.Scale(GetScreenWidth() * 0.5, GetScreenHeight() * 0.5, 0);

			if (triangle.color) {
				FillTriangle(
					(int)triangle.points[0].x, (int)triangle.points[0].y,
					(int)triangle.points[1].x, (int)triangle.points[1].y,
					(int)triangle.points[2].x, (int)triangle.points[2].y,
					PIXEL_HALF, triangle.color
				);
			}
		}
	}

	void OnDestroy() override {

	}
};

int main() {
	RubiksEngine engine(200, 200);
	engine.Run();
	return 0;
}