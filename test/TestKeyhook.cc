#include <stdio.h>
#include <Windows.h>
#include "../src/Utility.h"

const WORD VK_C = 67;
bool ctrl = false;
bool shift = false;
bool repeat = false;

void handle();


LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
	bool consume = false;

	if (nCode == HC_ACTION) {
		PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT) lParam;
		switch (wParam) {
			case WM_KEYUP:
			case WM_SYSKEYUP:
				switch (p->vkCode) {
					case VK_LCONTROL:
						ctrl = false;
						break;
					case VK_LSHIFT:
						shift = false;
						break;
					case VK_C:
						repeat = false;
						break;
				}
				break;
			case WM_KEYDOWN:
			case WM_SYSKEYDOWN:
				switch (p->vkCode) {
					case VK_LCONTROL:
						ctrl = true;
						break;
					case VK_LSHIFT:
						shift = true;
						break;
					case VK_C:
						consume = ctrl && shift;
						if (consume && !repeat) {
							repeat = true;
							handle();
						}
						break;
				}
		}
	}
	return consume ? 1 : CallNextHookEx(NULL, nCode, wParam, lParam);
}

void handle() {
	std::vector<std::pair<Utility::SendKeysState, std::vector<WORD>>> vkss = {
		// {Utility::SendKeysState::UP,   {VK_SHIFT}},
		{Utility::SendKeysState::TYPE, {'C', 'V', 'V'}},
		// {Utility::SendKeysState::DOWN, {VK_SHIFT}},
	};
	Utility::sendKeys(vkss);
}

int main() {
	HHOOK hhkLowLevelKybd = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
	MSG msg;
	while (!GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	UnhookWindowsHookEx(hhkLowLevelKybd);
}

// g++ -lgdi32 test\TestKeyhook.cc src\Utility.cc && a.exe
