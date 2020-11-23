#pragma once
#include <math.h>
#include <Windows.h>

class Engine {
private:
	bool isRunning;

	int screenWidth;
	int screenHeight;

	HANDLE screen;
	CHAR_INFO* bufferScreen;

	SMALL_RECT windowRect;

public:
	Engine(int width, int height);
	~Engine();

	void Run();

	virtual void OnCreate() = 0;
	virtual void OnUpdate(double deltaTime) = 0;
	virtual void OnDestroy() = 0;

	bool GetRunningState();
	void SetRunningState(bool runningState);
	int GetScreenWidth();
	int GetScreenHeight();

	void DrawPixel(int x, int y, wchar_t pixel, short color);
	void FillPixel(int x1, int y1, int x2, int y2, wchar_t pixel, short color);
	void DrawLine(int x1, int y1, int x2, int y2, wchar_t pixel, short color);
	void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, wchar_t pixel, short color);
	void FillTriangle(int x1, int y1, int x2, int y2, int x3, int y3, wchar_t pixel, short color);
};