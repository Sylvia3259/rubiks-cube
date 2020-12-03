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

	vector<string> GetCommandList() {
		vector<string> commandList;

		if (315 < thetaY || thetaY <= 45) {
			if (thetaX <= -45) {
				commandList = {
					"i1+", "k1+", "k1-", "i1-",
					"k2+", "k2-", "i0+", "i0-",
					"i2+", "i2-", "k0+", "k0-",
				};
			}
			else if (thetaX > 45) {
				commandList = {
					"i1+", "k1-", "k1+", "i1-",
					"k0-", "k0+", "i0+", "i0-",
					"i2+", "i2-", "k2-", "k2+",
				};
			}
			else {
				commandList = { 
					"i1+", "j1+", "j1-", "i1-", 
					"j2+", "j2-", "i0+", "i0-", 
					"i2+", "i2-", "j0+", "j0-",
				};
			}
		}
		else if (45 < thetaY && thetaY <= 135) {
			if (thetaX <= -45) {
				commandList = {
					"k1+", "i1-", "i1+", "k1-",
					"i0-", "i0+", "k0+", "k0-",
					"k2+", "k2-", "i2-", "i2+",
				};
			}
			else if (thetaX > 45) {
				commandList = {
					"k1+", "i1+", "i1-", "k1-",
					"i2+", "i2-", "k0+", "k0-",
					"k2+", "k2-", "i0+", "i0-",
				};
			}
			else {
				commandList = {
					"k1+", "j1+", "j1-", "k1-",
					"j2+", "j2-", "k0+", "k0-",
					"k2+", "k2-", "j0+", "j0-",
				};
			}
		}
		else if (135 < thetaY && thetaY <= 225) {
			if (thetaX <= -45) {
				commandList = {
					"i1-", "k1-", "k1+", "i1+",
					"k0-", "k0+", "i2-", "i2+",
					"i0-", "i0+", "k2-", "k2+",
				};
			}
			else if (thetaX > 45) {
				commandList = {
					"i1-", "k1+", "k1-", "i1+",
					"k2+", "k2-", "i2-", "i2+",
					"i0-", "i0+", "k0+", "k0-",
				};
			}
			else {
				commandList = {
					"i1-", "j1+", "j1-", "i1+",
					"j2+", "j2-", "i2-", "i2+",
					"i0-", "i0+", "j0+", "j0-",
				};
			}
		}
		else if (225 < thetaY && thetaY <= 315) {
			if (thetaX <= -45) {
				commandList = {
					"k1-", "i1+", "i1-", "k1+",
					"i2+", "i2-", "k2-", "k2+",
					"k0-", "k0+", "i0+", "i0-",
				};
			}
			else if (thetaX > 45) {
				commandList = {
					"k1-", "i1-", "i1+", "k1+",
					"i0-", "i0+", "k2-", "k2+",
					"k0-", "k0+", "i2-", "i2+",
				};
			}
			else {
				commandList = {
					"k1-", "j1+", "j1-", "k1+",
					"j2+", "j2-", "k2-", "k2+",
					"k0-", "k0+", "j0+", "j0-",
				};
			}
		}

		return commandList;
	}

public:
	RubiksEngine(short width, short height) : Engine(width, height) {
		thetaX = 45;
		thetaY = 45;
	}

	void OnCreate() override {
		srand(GetTickCount64());

		const char* symbols = "ijk";
		const char* indexes = "012";
		const char* directions = "+-";

		for (int i = 0; i < 20; ++i) {
			string command = "";
			command += symbols[rand() % 3];
			command += indexes[rand() % 3];
			command += directions[rand() % 2];

			rubiksCube.Control(command);
		}
	}

	void OnUpdate(double deltaTime) override {
		rubiksCube.Update(deltaTime);

		//유저 입력 처리
		inputManager.UpdateKeyStates();

		if (inputManager.GetKeyState(VK_UP) >= KeyPressed) {
			thetaX += deltaTime * 120;
			thetaX = MIN(thetaX, +60);
		}
		if (inputManager.GetKeyState(VK_DOWN) >= KeyPressed) {
			thetaX -= deltaTime * 120;
			thetaX = MAX(thetaX, -60);
		}
		if (inputManager.GetKeyState(VK_LEFT) >= KeyPressed) {
			thetaY -= deltaTime * 120;
			if (thetaY <= 0) thetaY += 360;
		}
		if (inputManager.GetKeyState(VK_RIGHT) >= KeyPressed) {
			thetaY += deltaTime * 120;
			if (thetaY >= 360) thetaY -= 360;
		}

		vector<string> commandList = GetCommandList();

		if (inputManager.GetKeyState(VK_NUMPAD5) == KeyPressed) {
			if (inputManager.GetKeyState(VK_NUMPAD2) == KeyDown)
				rubiksCube.Control(commandList[0]);
			else if (inputManager.GetKeyState(VK_NUMPAD4) == KeyDown)
				rubiksCube.Control(commandList[1]);
			else if (inputManager.GetKeyState(VK_NUMPAD6) == KeyDown)
				rubiksCube.Control(commandList[2]);
			else if (inputManager.GetKeyState(VK_NUMPAD8) == KeyDown)
				rubiksCube.Control(commandList[3]);
		}
		else if (inputManager.GetKeyState(VK_NUMPAD2) == KeyPressed) {
			if (inputManager.GetKeyState(VK_NUMPAD1) == KeyDown)
				rubiksCube.Control(commandList[4]);
			else if (inputManager.GetKeyState(VK_NUMPAD3) == KeyDown)
				rubiksCube.Control(commandList[5]);
		}
		else if (inputManager.GetKeyState(VK_NUMPAD4) == KeyPressed) {
			if (inputManager.GetKeyState(VK_NUMPAD1) == KeyDown)
				rubiksCube.Control(commandList[6]);
			else if (inputManager.GetKeyState(VK_NUMPAD7) == KeyDown)
				rubiksCube.Control(commandList[7]);
		}
		else if (inputManager.GetKeyState(VK_NUMPAD6) == KeyPressed) {
			if (inputManager.GetKeyState(VK_NUMPAD3) == KeyDown)
				rubiksCube.Control(commandList[8]);
			else if (inputManager.GetKeyState(VK_NUMPAD9) == KeyDown)
				rubiksCube.Control(commandList[9]);
		}
		else if (inputManager.GetKeyState(VK_NUMPAD8) == KeyPressed) {
			if (inputManager.GetKeyState(VK_NUMPAD7) == KeyDown)
				rubiksCube.Control(commandList[10]);
			else if (inputManager.GetKeyState(VK_NUMPAD9) == KeyDown)
				rubiksCube.Control(commandList[11]);
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