﻿#include "Triangle.h"
#include "Engine.h"
using namespace std;

class RubiksEngine : public Engine {
private:
	double theta;
	Triangle cube[12];
	Vector camera;

	CHAR_INFO GetPixelInfo(double light) {
		short backgroundColor = BG_BLACK, foregroundColor = FG_BLACK;
		wchar_t pixelType = PIXEL_SOLID;

		switch ((int)(light * 13)) {
		case 0: backgroundColor = BG_BLACK; foregroundColor = FG_BLACK; pixelType = PIXEL_SOLID; break;
		case 1: backgroundColor = BG_BLACK; foregroundColor = FG_DARK_GRAY; pixelType = PIXEL_QUARTER; break;
		case 2: backgroundColor = BG_BLACK; foregroundColor = FG_DARK_GRAY; pixelType = PIXEL_HALF; break;
		case 3: backgroundColor = BG_BLACK; foregroundColor = FG_DARK_GRAY; pixelType = PIXEL_THREEQUARTERS; break;
		case 4: backgroundColor = BG_BLACK; foregroundColor = FG_DARK_GRAY; pixelType = PIXEL_SOLID; break;
		case 5: backgroundColor = BG_DARK_GRAY; foregroundColor = FG_GRAY; pixelType = PIXEL_QUARTER; break;
		case 6: backgroundColor = BG_DARK_GRAY; foregroundColor = FG_GRAY; pixelType = PIXEL_HALF; break;
		case 7: backgroundColor = BG_DARK_GRAY; foregroundColor = FG_GRAY; pixelType = PIXEL_THREEQUARTERS; break;
		case 8: backgroundColor = BG_DARK_GRAY; foregroundColor = FG_GRAY; pixelType = PIXEL_SOLID; break;
		case 9:  backgroundColor = BG_GRAY; foregroundColor = FG_WHITE; pixelType = PIXEL_QUARTER; break;
		case 10: backgroundColor = BG_GRAY; foregroundColor = FG_WHITE; pixelType = PIXEL_HALF; break;
		case 11: backgroundColor = BG_GRAY; foregroundColor = FG_WHITE; pixelType = PIXEL_THREEQUARTERS; break;
		case 12: backgroundColor = BG_GRAY; foregroundColor = FG_WHITE; pixelType = PIXEL_SOLID; break;
		case 13: backgroundColor = BG_GRAY; foregroundColor = FG_WHITE; pixelType = PIXEL_SOLID; break;
		}

		CHAR_INFO c;
		c.Attributes = backgroundColor | foregroundColor;
		c.Char.UnicodeChar = pixelType;
		return c;
	}

public:
	RubiksEngine(short width, short height) : Engine(width, height) {
		theta = 0;
	}

	void OnCreate() override {
		cube[0] = Triangle(Vector(-1, -1, -1), Vector(-1, +1, -1), Vector(+1, +1, -1));
		cube[1] = Triangle(Vector(-1, -1, -1), Vector(+1, +1, -1), Vector(+1, -1, -1));

		cube[2] = Triangle(Vector(+1, -1, -1), Vector(+1, +1, -1), Vector(+1, +1, +1));
		cube[3] = Triangle(Vector(+1, -1, -1), Vector(+1, +1, +1), Vector(+1, -1, +1));

		cube[4] = Triangle(Vector(+1, -1, +1), Vector(+1, +1, +1), Vector(-1, +1, +1));
		cube[5] = Triangle(Vector(+1, -1, +1), Vector(-1, +1, +1), Vector(-1, -1, +1));

		cube[6] = Triangle(Vector(-1, -1, +1), Vector(-1, +1, +1), Vector(-1, +1, -1));
		cube[7] = Triangle(Vector(-1, -1, +1), Vector(-1, +1, -1), Vector(-1, -1, -1));

		cube[8] = Triangle(Vector(-1, +1, -1), Vector(-1, +1, +1), Vector(+1, +1, +1));
		cube[9] = Triangle(Vector(-1, +1, -1), Vector(+1, +1, +1), Vector(+1, +1, -1));

		cube[10] = Triangle(Vector(+1, -1, +1), Vector(-1, -1, +1), Vector(-1, -1, -1));
		cube[11] = Triangle(Vector(+1, -1, +1), Vector(-1, -1, -1), Vector(+1, -1, -1));
	}

	void OnUpdate(double deltaTime) override {
		theta += deltaTime * 1.5;

		for (const auto& triangle : cube) {
			Triangle tempTriangle = triangle;

			tempTriangle.Rotate(theta * 1.0, theta * 0.5, theta * 0.75);
			tempTriangle.Translate(0, 0, 5);

			Vector line1, line2, normal;
			line1 = tempTriangle.points[1] - tempTriangle.points[0];
			line2 = tempTriangle.points[2] - tempTriangle.points[0];
			normal = line1.Cross(line2);
			normal.Normalize();

			if (normal.Dot(tempTriangle.points[0] - camera) < 0) {
				Vector lightSource(0, 0, -1);
				lightSource.Normalize();

				double light = normal.x * lightSource.x + normal.y * lightSource.y + normal.z * lightSource.z;
				CHAR_INFO pixel = GetPixelInfo(light);

				tempTriangle.Project(0.1, 1000, 90, (double)GetScreenWidth() / GetScreenHeight());

				tempTriangle.Translate(1, 1, 0);
				tempTriangle.Scale(GetScreenWidth() * 0.5, GetScreenHeight() * 0.5, 0);

				FillTriangle(
					(int)tempTriangle.points[0].x, (int)tempTriangle.points[0].y,
					(int)tempTriangle.points[1].x, (int)tempTriangle.points[1].y,
					(int)tempTriangle.points[2].x, (int)tempTriangle.points[2].y,
					pixel.Char.UnicodeChar, pixel.Attributes
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