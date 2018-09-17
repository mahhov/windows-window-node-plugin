#include <windows.h>
#include <stdio.h>

INPUT getKeyboardInput(WORD vk, DWORD flags = 0) {
	INPUT input = {INPUT_KEYBOARD};
	input.ki = {vk, 0, flags, 0, 0};
	return input;
}

int main() {
	Sleep(1000);

	INPUT ctrlDown = getKeyboardInput(VK_CONTROL);
	INPUT cDown = getKeyboardInput('C');
	INPUT ctrlUp = getKeyboardInput(VK_CONTROL, KEYEVENTF_KEYUP);
	INPUT cUp = getKeyboardInput('C', KEYEVENTF_KEYUP);
	INPUT inputs[] = {ctrlDown, cDown, ctrlUp, cUp};
	SendInput(4, inputs, sizeof(INPUT));
}

// g++ -lgdi32 test\TestSendInput.cc && a.exe