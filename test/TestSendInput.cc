#include <windows.h>
#include <stdio.h>

INPUT makeKeyInput(WORD vk, DWORD flags = 0) {
	INPUT input = {INPUT_KEYBOARD};
	input.ki = {vk, 0, flags, 0, 0};
	return input;
}

int main() {
	printf("wait 3 seconds\n");
	Sleep(3000);

	printf("pressing\n");
	INPUT ctrlDown = makeKeyInput(VK_CONTROL);
	INPUT cDown = makeKeyInput('C');
	INPUT shiftUP = makeKeyInput(VK_SHIFT, KEYEVENTF_KEYUP);
	INPUT ctrlUp = makeKeyInput(VK_CONTROL, KEYEVENTF_KEYUP);
	INPUT cUp = makeKeyInput('C', KEYEVENTF_KEYUP);
	INPUT inputs[] = {shiftUP, ctrlUp, cUp, ctrlDown, cDown, ctrlUp, cUp};
	SendInput(7, inputs, sizeof(INPUT));
	printf("complete\n");
}

// g++ -lgdi32 test\TestSendInput.cc && a.exe