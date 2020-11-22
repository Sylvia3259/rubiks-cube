#include "Engine.h"

Engine::Engine(int width, int height) {
	screenWidth = width;
	screenHeight = height;

	screen = GetStdHandle(STD_OUTPUT_HANDLE);
	bufferScreen = new CHAR_INFO[screenWidth * screenHeight];
	memset(bufferScreen, 0, sizeof(CHAR_INFO) * screenWidth * screenHeight);

	CONSOLE_FONT_INFOEX font;
	font.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	font.nFont = 0;
	font.dwFontSize.X = 4;
	font.dwFontSize.Y = 4;
	font.FontFamily = FF_DONTCARE;
	font.FontWeight = FW_NORMAL;
	wcscpy_s(font.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(screen, FALSE, &font);

	SMALL_RECT window = { 0, 0, screenWidth - 1, screenHeight - 1 };
	SetConsoleWindowInfo(screen, TRUE, &window);
}

Engine::~Engine() {
	delete[] bufferScreen;
}

void Engine::Run(double deltaTime) {
	isRunning = true;

	OnCreate();
	ULONGLONG oldTime = GetTickCount64(), currentTime;
	while (isRunning) {
		currentTime = GetTickCount64();
		OnUpdate((currentTime - oldTime) * 0.001);
		oldTime = currentTime;
	}
	OnDestroy();
}

inline bool Engine::GetRunningState() {
	return isRunning;
}

inline void Engine::SetRunningState(bool runningState) {
	isRunning = runningState;
}

inline int Engine::GetScreenWidth() {
	return screenWidth;
}

inline int Engine::GetScreenHeight() {
	return screenHeight;
}

inline void Engine::DrawPixel(int x, int y, wchar_t pixel, short color) {
	if ((0 <= x && x < screenWidth) && (0 <= y && y < screenHeight)) {
		bufferScreen[y * screenWidth + x].Char.UnicodeChar = pixel;
		bufferScreen[y * screenWidth + x].Attributes = color;
	}
}

inline void Engine::FillPixel(int x1, int y1, int x2, int y2, wchar_t pixel, short color) {
	if ((0 <= x1 && x1 < screenWidth) && (0 <= y1 && y1 < screenHeight))
		if ((0 <= x2 && x2 < screenWidth) && (0 <= y2 && y2 < screenHeight))
			for (int y = y1; y < y2; ++y)
				for (int x = x1; x < x2; ++x)
					DrawPixel(x, y, pixel, color);
}

void Engine::DrawLine(int x1, int y1, int x2, int y2, wchar_t pixel, short color) {
	int dx = x2 - x1;
	int ix = (dx > 0) - (dx < 0);
	int dy = y2 - y1;
	int iy = (dy > 0) - (dy < 0);
	int err;

	dx = abs(dx) << 1;
	dy = abs(dy) << 1;

	DrawPixel(x1, y1, pixel, color);

	if (dx >= dy) {
		err = dy - (dx >> 1);
		while (x1 != x2) {
			if (err >= 0) {
				if ((err != 0) || (ix > 0)) {
					y1 += iy;
					err -= dx;
				}
			}
			x1 += ix;
			err += dy;

			DrawPixel(x1, y1, pixel, color);
		}
	}
	else {
		err = dx - (dy >> 1);
		while (y1 != y2) {
			if (err >= 0) {
				if ((err != 0) || (iy > 0)) {
					x1 += ix;
					err -= dy;
				}
			}
			y1 += iy;
			err += dx;

			DrawPixel(x1, y1, pixel, color);
		}
	}
}

void Engine::DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, wchar_t pixel, short color) {
	DrawLine(x1, y1, x2, y2, pixel, color);
	DrawLine(x2, y2, x3, y3, pixel, color);
	DrawLine(x3, y3, x1, y1, pixel, color);
}

void Engine::FillTriangle(int x1, int y1, int x2, int y2, int x3, int y3, wchar_t pixel, short color) {
	auto SWAP = [](int& x, int& y) { 
		int t = x; 
		x = y;
		y = t; 
	};
	auto drawline = [&](int sx, int ex, int ny) { 
		for (int i = sx; i <= ex; i++) 
			DrawPixel(i, ny, pixel, color); 
	};

	int t1x, t2x, y, minx, maxx, t1xp, t2xp;
	bool changed1 = false;
	bool changed2 = false;
	int signx1, signx2, dx1, dy1, dx2, dy2;
	int e1, e2;

	if (y1 > y2) { 
		SWAP(y1, y2); 
		SWAP(x1, x2); 
	}
	if (y1 > y3) { 
		SWAP(y1, y3); 
		SWAP(x1, x3); 
	}
	if (y2 > y3) { 
		SWAP(y2, y3); 
		SWAP(x2, x3); 
	}

	t1x = t2x = x1; y = y1;
	dx1 = (int)(x2 - x1); 
	if (dx1 < 0) { 
		dx1 = -dx1; 
		signx1 = -1; 
	}
	else signx1 = 1;
	dy1 = (int)(y2 - y1);

	dx2 = (int)(x3 - x1); 
	if (dx2 < 0) { 
		dx2 = -dx2; 
		signx2 = -1; 
	}
	else signx2 = 1;
	dy2 = (int)(y3 - y1);

	if (dy1 > dx1) {
		SWAP(dx1, dy1);
		changed1 = true;
	}
	if (dy2 > dx2) {
		SWAP(dy2, dx2);
		changed2 = true;
	}

	e2 = (int)(dx2 >> 1);
	if (y1 == y2) goto next;
	e1 = (int)(dx1 >> 1);

	for (int i = 0; i < dx1;) {
		t1xp = 0; t2xp = 0;
		if (t1x < t2x) { 
			minx = t1x; 
			maxx = t2x; 
		}
		else { 
			minx = t2x; 
			maxx = t1x; 
		}
		while (i < dx1) {
			i++;
			e1 += dy1;
			while (e1 >= dx1) {
				e1 -= dx1;
				if (changed1) t1xp = signx1;
				else goto next1;
			}
			if (changed1) break;
			else t1x += signx1;
		}
	next1:
		while (1) {
			e2 += dy2;
			while (e2 >= dx2) {
				e2 -= dx2;
				if (changed2) t2xp = signx2;
				else goto next2;
			}
			if (changed2) break;
			else t2x += signx2;
		}
	next2:
		if (minx > t1x) minx = t1x; 
		if (minx > t2x) minx = t2x;
		if (maxx < t1x) maxx = t1x; 
		if (maxx < t2x) maxx = t2x;
		drawline(minx, maxx, y);
		if (!changed1) t1x += signx1;
		t1x += t1xp;
		if (!changed2) t2x += signx2;
		t2x += t2xp;
		y += 1;
		if (y == y2) break;
	}
next:
	dx1 = (int)(x3 - x2); 
	if (dx1 < 0) { 
		dx1 = -dx1; 
		signx1 = -1; 
	}
	else signx1 = 1;
	dy1 = (int)(y3 - y2);
	t1x = x2;

	if (dy1 > dx1) {
		SWAP(dy1, dx1);
		changed1 = true;
	}
	else changed1 = false;

	e1 = (int)(dx1 >> 1);

	for (int i = 0; i <= dx1; i++) {
		t1xp = 0; t2xp = 0;
		if (t1x < t2x) { 
			minx = t1x; 
			maxx = t2x; 
		}
		else { 
			minx = t2x; 
			maxx = t1x; 
		}
		while (i < dx1) {
			e1 += dy1;
			while (e1 >= dx1) {
				e1 -= dx1;
				if (changed1) { 
					t1xp = signx1;
					break; 
				}
				else goto next3;
			}
			if (changed1) break;
			else t1x += signx1;
			if (i < dx1) i++;
		}
	next3:
		while (t2x != x3) {
			e2 += dy2;
			while (e2 >= dx2) {
				e2 -= dx2;
				if (changed2) t2xp = signx2;
				else goto next4;
			}
			if (changed2) break;
			else t2x += signx2;
		}
	next4:
		if (minx > t1x) minx = t1x; 
		if (minx > t2x) minx = t2x;
		if (maxx < t1x) maxx = t1x; 
		if (maxx < t2x) maxx = t2x;
		drawline(minx, maxx, y);
		if (!changed1) t1x += signx1;
		t1x += t1xp;
		if (!changed2) t2x += signx2;
		t2x += t2xp;
		y += 1;
		if (y > y3) return;
	}
}