#include "Input.h"

Input::Input() {
	memset(oldKeyStates, false, 256);
	memset(newKeyStates, false, 256);
}

void Input::UpdateKeyStates() {
	for (int i = 0; i < 256; ++i) {
		oldKeyStates[i] = newKeyStates[i];
		newKeyStates[i] = GetAsyncKeyState(i) & 0x8000;
	}
}

int Input::GetKeyState(int vKey) {
	return -oldKeyStates[vKey & 0xFF] + newKeyStates[vKey & 0xFF] * 2;
}