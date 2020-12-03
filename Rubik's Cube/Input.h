#pragma once
#include <Windows.h>

class Input {
private:
	bool oldKeyStates[256];
	bool newKeyStates[256];

public:
	Input();

	void UpdateKeyStates();
	int GetKeyState(int vKey);
};