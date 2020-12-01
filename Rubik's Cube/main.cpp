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

	}

	void OnUpdate(double deltaTime) override {
		theta += deltaTime * 1.5; 

		vector<Cube*> cubes;
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				for (int k = 0; k < 3; ++k)
					cubes.push_back(&rubiksCube.cubes[i][j][k]);

		vector<Triangle> triangles;
		for (Cube* const cube : cubes) {
			for (const Triangle& triangle : cube->polygons) {
				Triangle tempTriangle = triangle;

				tempTriangle.Rotate(theta * 1.0, theta * 0.5, theta * 0.75);
				tempTriangle.Translate(0, 0, 10);

				Vector line1, line2, normal;
				line1 = tempTriangle.points[1] - tempTriangle.points[0];
				line2 = tempTriangle.points[2] - tempTriangle.points[0];
				normal = line1.Cross(line2);
				normal.Normalize();

				if (normal.Dot(tempTriangle.points[0]) < 0)
					triangles.push_back(tempTriangle);
			}
		}

		sort(triangles.begin(), triangles.end(), 
			[](const Triangle& lhs, const Triangle& rhs) {
				return lhs.color < rhs.color;
			});

		for (const Triangle& triangle : triangles) {
			Triangle tempTriangle = triangle;

			tempTriangle.Project(0.1, 1000, 90, (double)GetScreenWidth() / GetScreenHeight());

			tempTriangle.Translate(1, 1, 0);
			tempTriangle.Scale(GetScreenWidth() * 0.5, GetScreenHeight() * 0.5, 0);

			FillTriangle(
				(int)tempTriangle.points[0].x, (int)tempTriangle.points[0].y,
				(int)tempTriangle.points[1].x, (int)tempTriangle.points[1].y,
				(int)tempTriangle.points[2].x, (int)tempTriangle.points[2].y,
				PIXEL_HALF, tempTriangle.color
			);
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