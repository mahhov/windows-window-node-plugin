#include "KeyCatcher.h"

KeyCatcher* KeyCatcher::callbackThis = nullptr;

void KeyCatcher::begin() {
	hhook = SetWindowsHookEx(WH_KEYBOARD_LL, process, NULL, 0);
	callbackThis = this;
}

void KeyCatcher::stop() {
	UnhookWindowsHookEx(hhook);
}

void KeyCatcher::setCallback(std::function<bool(bool down, int code, bool injected)> callback) {
	this->callback = std::move(callback);
}

void KeyCatcher::update() {
	MSG msg;
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

LRESULT CALLBACK KeyCatcher::process(int code, WPARAM wParam, LPARAM lParam) {
	bool consume = false;
	if (code == HC_ACTION && callbackThis != nullptr && callbackThis->callback != nullptr) {
		KBDLLHOOKSTRUCT* event = (KBDLLHOOKSTRUCT*) lParam;
		bool injected = event->flags & LLKHF_INJECTED;
		switch (wParam) {
			case WM_KEYUP:
			case WM_SYSKEYUP:
				consume = callbackThis->callback(false, event->vkCode, injected);
				break;
			case WM_KEYDOWN:
			case WM_SYSKEYDOWN:
				consume = callbackThis->callback(true, event->vkCode, injected);
				break;
		}
	}
	return consume ? 1 : CallNextHookEx(NULL, code, wParam, lParam);
}
