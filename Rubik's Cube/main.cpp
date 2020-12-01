#include "Rubiks.h"
#include "Engine.h"
using namespace std;

class RubiksEngine : public Engine {
private:
	double theta;
	Rubiks cube;

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

	}

	void OnUpdate(double deltaTime) override {
		theta += deltaTime * 1.5;

		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				for (int k = 0; k < 3; ++k) {
					for (const auto& triangle : cube.cubes[i][j][k]) {
						Triangle tempTriangle = triangle;

						tempTriangle.Rotate(theta * 1.0, theta * 0.5, theta * 0.75);
						tempTriangle.Translate(0, 0, 10);

						Vector line1, line2, normal;
						line1 = tempTriangle.points[1] - tempTriangle.points[0];
						line2 = tempTriangle.points[2] - tempTriangle.points[0];
						normal = line1.Cross(line2);
						normal.Normalize();

						if (normal.Dot(tempTriangle.points[0]) < 0) {
							Vector lightSource(0, 0, -1);
							lightSource.Normalize();

							//double light = normal.Dot(lightSource);
							//CHAR_INFO pixel = GetPixelInfo(light);

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
				}
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