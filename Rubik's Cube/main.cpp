#include <algorithm>
#include <random>
#include "Rubiks.h"
#include "Engine.h"
#include "Input.h"
#include "macros.h"
#include "constants.h"
using namespace std;

class RubiksEngine : public Engine {
public:
	RubiksEngine(short width, short height) : Engine(width, height) {
		thetaX = 45;
		thetaY = 45;
	}

	void OnCreate() override {
		const string symbols = "ijk";
		const string indexes = "012";
		const string directions = "+-";

		default_random_engine randomEngine(random_device{}());
		uniform_int_distribution<int> symbolRange(0, 2);
		uniform_int_distribution<int> indexRange(0, 2);
		uniform_int_distribution<int> directionRange(0, 1);

		for (int i = 0; i < shuffleCount; ++i) {
			string command = "";
			command += symbols[symbolRange(randomEngine)];
			command += indexes[indexRange(randomEngine)];
			command += directions[directionRange(randomEngine)];

			rubiksCube.Control(command);
		}
	}

	void OnUpdate(double deltaTime) override {
		HandleUserInput(deltaTime);

		rubiksCube.Update(deltaTime);

		Rubiks tempCube = rubiksCube;
		tempCube.Rotate(0, thetaY, 0);
		tempCube.Rotate(thetaX, 0, 0);
		tempCube.Translate(0, 0, 10);

		vector<Triangle> polygons;
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				for (int k = 0; k < 3; ++k) {
					for (const auto& polygon : tempCube.cubes[i][j][k].polygons) {
						Vector line1 = polygon.points[1] - polygon.points[0];
						Vector line2 = polygon.points[2] - polygon.points[0];
						Vector normal = line1.Cross(line2);
						normal.Normalize();

						if (normal.Dot(polygon.points[0]) < 0)
							polygons.push_back(polygon);
					}
				}
			}
		}

		sort(polygons.begin(), polygons.end(),
			[](const Triangle& lhs, const Triangle& rhs) {
				const double lhsAverageZ = lhs.points[0].z + lhs.points[1].z + lhs.points[2].z;
				const double rhsAverageZ = rhs.points[0].z + rhs.points[1].z + rhs.points[2].z;
				return lhsAverageZ > rhsAverageZ;
			});

		for (auto& polygon : polygons) {
			polygon.Project(0.1, 1000, 90, (double)GetScreenWidth() / GetScreenHeight());
			polygon.Translate(1, 1, 0);
			polygon.Scale(GetScreenWidth() * 0.5, GetScreenHeight() * 0.5, 0);

			if (polygon.color) {
				DrawTriangle(
					(int)polygon.points[0].x, (int)polygon.points[0].y,
					(int)polygon.points[1].x, (int)polygon.points[1].y,
					(int)polygon.points[2].x, (int)polygon.points[2].y,
					PIXEL_HALF, polygon.color
				);
			}
		}
	}

	void OnDestroy() override {

	}

private:
	vector<string> GetCommandList() {
		if (315 < thetaY || thetaY <= 45) {
			if (thetaX <= -45)
				return commandLists[0][0];
			else if (-45 < thetaX && thetaX <= 45)
				return commandLists[0][1];
			else if (45 < thetaX)
				return commandLists[0][2];
		}
		else if (45 < thetaY && thetaY <= 135) {
			if (thetaX <= -45)
				return commandLists[1][0];
			else if (-45 < thetaX && thetaX <= 45)
				return commandLists[1][1];
			else if (45 < thetaX)
				return commandLists[1][2];
		}
		else if (135 < thetaY && thetaY <= 225) {
			if (thetaX <= -45)
				return commandLists[2][0];
			else if (-45 < thetaX && thetaX <= 45)
				return commandLists[2][1];
			else if (45 < thetaX)
				return commandLists[2][2];
		}
		else if (225 < thetaY && thetaY <= 315) {
			if (thetaX <= -45)
				return commandLists[3][0];
			else if (-45 < thetaX && thetaX <= 45)
				return commandLists[3][1];
			else if (45 < thetaX)
				return commandLists[3][2];
		}
		return commandLists[0][0];
	}

	void HandleUserInput(double deltaTime) {
		inputManager.UpdateKeyStates();

		if (inputManager.GetKeyState(VK_ESCAPE) == keyDown)
			Stop();

		if (inputManager.GetKeyState(VK_UP) >= keyPressed) {
			thetaX += deltaTime * rotateSpeed;
			thetaX = MIN(thetaX, +60);
		}
		if (inputManager.GetKeyState(VK_DOWN) >= keyPressed) {
			thetaX -= deltaTime * rotateSpeed;
			thetaX = MAX(thetaX, -60);
		}
		if (inputManager.GetKeyState(VK_LEFT) >= keyPressed) {
			thetaY -= deltaTime * rotateSpeed;
			if (thetaY <= 0) thetaY += 360;
		}
		if (inputManager.GetKeyState(VK_RIGHT) >= keyPressed) {
			thetaY += deltaTime * rotateSpeed;
			if (thetaY >= 360) thetaY -= 360;
		}

		if (inputManager.GetKeyState(VK_NUMPAD5) == keyPressed) {
			if (inputManager.GetKeyState(VK_NUMPAD2) == keyDown)
				rubiksCube.Control(GetCommandList()[0]);
			else if (inputManager.GetKeyState(VK_NUMPAD4) == keyDown)
				rubiksCube.Control(GetCommandList()[1]);
			else if (inputManager.GetKeyState(VK_NUMPAD6) == keyDown)
				rubiksCube.Control(GetCommandList()[2]);
			else if (inputManager.GetKeyState(VK_NUMPAD8) == keyDown)
				rubiksCube.Control(GetCommandList()[3]);
		}
		else if (inputManager.GetKeyState(VK_NUMPAD2) == keyPressed) {
			if (inputManager.GetKeyState(VK_NUMPAD1) == keyDown)
				rubiksCube.Control(GetCommandList()[4]);
			else if (inputManager.GetKeyState(VK_NUMPAD3) == keyDown)
				rubiksCube.Control(GetCommandList()[5]);
		}
		else if (inputManager.GetKeyState(VK_NUMPAD4) == keyPressed) {
			if (inputManager.GetKeyState(VK_NUMPAD1) == keyDown)
				rubiksCube.Control(GetCommandList()[6]);
			else if (inputManager.GetKeyState(VK_NUMPAD7) == keyDown)
				rubiksCube.Control(GetCommandList()[7]);
		}
		else if (inputManager.GetKeyState(VK_NUMPAD6) == keyPressed) {
			if (inputManager.GetKeyState(VK_NUMPAD3) == keyDown)
				rubiksCube.Control(GetCommandList()[8]);
			else if (inputManager.GetKeyState(VK_NUMPAD9) == keyDown)
				rubiksCube.Control(GetCommandList()[9]);
		}
		else if (inputManager.GetKeyState(VK_NUMPAD8) == keyPressed) {
			if (inputManager.GetKeyState(VK_NUMPAD7) == keyDown)
				rubiksCube.Control(GetCommandList()[10]);
			else if (inputManager.GetKeyState(VK_NUMPAD9) == keyDown)
				rubiksCube.Control(GetCommandList()[11]);
		}
	}

private:
	double thetaX, thetaY;
	Rubiks rubiksCube;
	Input inputManager;
};

int main() {
	SetConsoleTitle(L"Rubik's Cube");

	RubiksEngine engine(200, 200);
	engine.Run();

	return 0;
}