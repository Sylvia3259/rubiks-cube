#pragma once
#include <math.h>
#include <Windows.h>
#include "constants.h"

class Engine {
private:
	bool isRunning;

	HANDLE consoleHandle;
	COORD consoleSize;
	SMALL_RECT console;
	CHAR_INFO* consoleBuffer;

public:
	Engine(short width, short height);
	~Engine();

	void Run();
	void Stop();

	virtual void OnCreate() = 0;
	virtual void OnUpdate(double deltaTime) = 0;
	virtual void OnDestroy() = 0;

	short GetScreenWidth() const noexcept;
	short GetScreenHeight() const noexcept;

	void DrawPixel(int x, int y, wchar_t pixel, short color);
	void DrawLine(int x1, int y1, int x2, int y2, wchar_t pixel, short color);
	void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, wchar_t pixel, short color);
	void FillTriangle(int x1, int y1, int x2, int y2, int x3, int y3, wchar_t pixel, short color);
};