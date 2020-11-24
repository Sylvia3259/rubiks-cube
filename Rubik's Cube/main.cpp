#include "Engine.h"
#include "Triangle.h"
using namespace std;

class RubiksEngine : public Engine {
private:
	double theta;
	Triangle cube[12];
	Vector camera;

	CHAR_INFO GetPixelInfo(double lum)
	{
		short backgroundColor, foregroundColor;
		wchar_t pixelType;

		switch ((int)(13 * lum))
		{
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

		default: backgroundColor = BG_BLACK; foregroundColor = FG_BLACK; pixelType = PIXEL_SOLID;
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

	bool OnCreate() override {
		cube[0] = Triangle(-1, -1, -1, -1, 1, -1, 1, 1, -1);
		cube[1] = Triangle(-1, -1, -1, 1, 1, -1, 1, -1, -1);

		cube[2] = Triangle(1, -1, -1, 1, 1, -1, 1, 1, 1);
		cube[3] = Triangle(1, -1, -1, 1, 1, 1, 1, -1, 1);

		cube[4] = Triangle(1, -1, 1, 1, 1, 1, -1, 1, 1);
		cube[5] = Triangle(1, -1, 1, -1, 1, 1, -1, -1, 1);

		cube[6] = Triangle(-1, -1, 1, -1, 1, 1, -1, 1, -1);
		cube[7] = Triangle(-1, -1, 1, -1, 1, -1, -1, -1, -1);

		cube[8] = Triangle(-1, 1, -1, -1, 1, 1, 1, 1, 1);
		cube[9] = Triangle(-1, 1, -1, 1, 1, 1, 1, 1, -1);

		cube[10] = Triangle(1, -1, 1, -1, -1, 1, -1, -1, -1);
		cube[11] = Triangle(1, -1, 1, -1, -1, -1, 1, -1, -1);

		return true;
	}

	bool OnUpdate(double deltaTime) override {
		theta += deltaTime * 1.5;

		for (const auto& triangle : cube) {
			Triangle tempTriangle(triangle);

			tempTriangle.Rotate(theta * 1.0, theta * 0.5, theta * 0.75);
			tempTriangle.Translate(0, 0, 5);

			Vector normal, line1, line2;
			line1.x = tempTriangle.point[1].x - tempTriangle.point[0].x;
			line1.y = tempTriangle.point[1].y - tempTriangle.point[0].y;
			line1.z = tempTriangle.point[1].z - tempTriangle.point[0].z;

			line2.x = tempTriangle.point[2].x - tempTriangle.point[0].x;
			line2.y = tempTriangle.point[2].y - tempTriangle.point[0].y;
			line2.z = tempTriangle.point[2].z - tempTriangle.point[0].z;

			normal.x = line1.y * line2.z - line1.z * line2.y;
			normal.y = line1.z * line2.x - line1.x * line2.z;
			normal.z = line1.x * line2.y - line1.y * line2.x;
			normal.Normalize();

			if (normal.x * (tempTriangle.point[0].x - camera.x) +
				normal.y * (tempTriangle.point[0].y - camera.y) +
				normal.z * (tempTriangle.point[0].z - camera.z) < 0.0f)
			{
				Vector lightDirection(0, 0, -1);
				lightDirection.Normalize();

				float lum = normal.x * lightDirection.x + normal.y * lightDirection.y + normal.z * lightDirection.z;
				CHAR_INFO pixel = GetPixelInfo(lum);

				tempTriangle.Project(0.1, 1000, 90, (double)GetScreenHeight() / GetScreenWidth());

				tempTriangle.point[0].x += 1;
				tempTriangle.point[0].y += 1;

				tempTriangle.point[1].x += 1;
				tempTriangle.point[1].y += 1;

				tempTriangle.point[2].x += 1;
				tempTriangle.point[2].y += 1;

				tempTriangle.point[0].x *= GetScreenWidth() * 0.5;
				tempTriangle.point[0].y *= GetScreenHeight() * 0.5;

				tempTriangle.point[1].x *= GetScreenWidth() * 0.5;
				tempTriangle.point[1].y *= GetScreenHeight() * 0.5;

				tempTriangle.point[2].x *= GetScreenWidth() * 0.5;
				tempTriangle.point[2].y *= GetScreenHeight() * 0.5;

				FillTriangle(
					(int)tempTriangle.point[0].x, (int)tempTriangle.point[0].y,
					(int)tempTriangle.point[1].x, (int)tempTriangle.point[1].y,
					(int)tempTriangle.point[2].x, (int)tempTriangle.point[2].y,
					pixel.Char.UnicodeChar, pixel.Attributes
				);
			}
		}

		return true;
	}

	bool OnDestroy() override {
		return true;
	}
};

int main() {
	RubiksEngine engine(200, 200);
	engine.Run();
	return 0;
}