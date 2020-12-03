#include <algorithm>
#include "Rubiks.h"
#include "Engine.h"
#include "Input.h"
using namespace std;

class RubiksEngine : public Engine {
private:
	double thetaX, thetaY;
	Rubiks rubiksCube;
	Input inputManager;

public:
	RubiksEngine(short width, short height) : Engine(width, height) {
		thetaX = 0;
		thetaY = 0;
	}

	void OnCreate() override {

	}

	void OnUpdate(double deltaTime) override {
		rubiksCube.Update(deltaTime);

		//유저 입력 처리
		inputManager.UpdateKeyStates();

		if (inputManager.GetKeyState('W')) {
			thetaX -= deltaTime * 90;
			thetaX = MAX(thetaX, -60);
		}
		if (inputManager.GetKeyState('A')) {
			thetaY += deltaTime * 90;
			if (thetaY >= 360) thetaY -= 360;
		}
		if (inputManager.GetKeyState('S')) {
			thetaX += deltaTime * 90;
			thetaX = MIN(thetaX, +60);
		}
		if (inputManager.GetKeyState('D')) {
			thetaY -= deltaTime * 90;
			if (thetaY <= 0) thetaY += 360;
		}

		//큐브 렌더링
		Rubiks tempCube = rubiksCube;
		tempCube.Rotate(0, thetaY, 0);
		tempCube.Rotate(thetaX, 0, 0);
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