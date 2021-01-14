#include "Engine.h"

Engine::Engine(short width, short height) {
	isRunning = false;

	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX font = { sizeof(font), 0, { 4, 4 }, FF_DONTCARE, FW_NORMAL, L"" };
	SetCurrentConsoleFontEx(consoleHandle, FALSE, &font);
	CONSOLE_CURSOR_INFO cursorInfo = { 1, FALSE };
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
	consoleSize = { width, height };
	SetConsoleScreenBufferSize(consoleHandle, consoleSize);
	console = { 0, 0, width - 1, height - 1 };
	SetConsoleWindowInfo(consoleHandle, TRUE, &console);
	consoleBuffer = new CHAR_INFO[(long long)width * height];
}

Engine::~Engine() {
	delete[] consoleBuffer;
}

void Engine::Run() {
	isRunning = true;

	OnCreate();
	LARGE_INTEGER previousTime, currentTime, frequency;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&currentTime);
	while (isRunning) {
		previousTime = currentTime;
		QueryPerformanceCounter(&currentTime);
		memset(consoleBuffer, 0, sizeof(CHAR_INFO) * consoleSize.X * consoleSize.Y);
		OnUpdate((double)(currentTime.QuadPart - previousTime.QuadPart) / frequency.QuadPart);
		WriteConsoleOutput(consoleHandle, consoleBuffer, { consoleSize.X, consoleSize.Y }, { 0, 0 }, &console);
	}
	OnDestroy();
}

void Engine::Stop() {
	isRunning = false;
}

short Engine::GetScreenWidth() const noexcept {
	return consoleSize.X;
}

short Engine::GetScreenHeight() const noexcept {
	return consoleSize.Y;
}

void Engine::DrawPixel(int x, int y, wchar_t pixel, short color) {
	if ((console.Left <= x && x <= console.Right) && (console.Top <= y && y <= console.Bottom)) {
		consoleBuffer[y * consoleSize.X + x].Char.UnicodeChar = pixel;
		consoleBuffer[y * consoleSize.X + x].Attributes = color;
	}
}

void Engine::DrawLine(int x1, int y1, int x2, int y2, wchar_t pixel, short color) {
	int dx = x2 - x1;
	int ix = (dx > 0) - (dx < 0);
	int dy = y2 - y1;
	int iy = (dy > 0) - (dy < 0);
	int err;

	dx = ABS(dx) << 1;
	dy = ABS(dy) << 1;

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
	if (y1 > y3) {
		SWAP(int, x1, x3);
		SWAP(int, y1, y3);
	}
	if (y1 > y2) {
		SWAP(int, x1, x2);
		SWAP(int, y1, y2);
	}
	if (y2 > y3) {
		SWAP(int, x2, x3);
		SWAP(int, y2, y3);
	}

	int x4 = (int)(x1 + ((float)(y2 - y1) / (y3 - y1)) * (x3 - x1));

	float cx1 = (float)x1;
	float cx2 = (float)x1;
	float cx3 = (float)x3;
	float cx4 = (float)x3;

	float dx1 = (float)(x2 - x1) / (y2 - y1);
	float dx2 = (float)(x4 - x1) / (y2 - y1);
	float dx3 = (float)(x3 - x2) / (y3 - y2);
	float dx4 = (float)(x3 - x4) / (y3 - y2);

	for (int y = y1; y <= y2; ++y) {
		DrawLine((int)cx1, y, (int)cx2, y, pixel, color);
		cx1 += dx1;
		cx2 += dx2;
	}

	for (int y = y3; y >= y2; --y) {
		DrawLine((int)cx3, y, (int)cx4, y, pixel, color);
		cx3 -= dx3;
		cx4 -= dx4;
	}
}