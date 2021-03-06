#include "Utility.h"

std::string Utility::getClipboardText() {
	// https://stackoverflow.com/a/14763025/6951428
	if (!OpenClipboard(nullptr))
		return "";
	HANDLE hData = GetClipboardData(CF_TEXT);
	if (hData == nullptr)
		return "";
	char* pszText = static_cast<char*> (GlobalLock(hData));
	if (pszText == nullptr)
		return "";
	std::string text(pszText);
	GlobalUnlock(hData);
	CloseClipboard();
	return text;
}

void Utility::setClipboardText(std::string text) {
	OpenClipboard(nullptr);
	EmptyClipboard();
	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, text.size() + 1);
	if (!hg) {
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg), text.c_str(), text.size() + 1);
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
}

void Utility::clearClipboardText() {
	OpenClipboard(nullptr);
	EmptyClipboard();
	CloseClipboard();
}

void Utility::sendKeys(std::vector<std::pair<SendKeysState, std::vector<WORD>>> vkss) {
	std::vector<INPUT> inputs;
	for (auto vks : vkss)
		switch (vks.first) {
			case UP:
				for (auto vk : vks.second)
					inputs.push_back(makeKeyInput(vk, true));
				break;
			case DOWN:
				for (auto vk : vks.second)
					inputs.push_back(makeKeyInput(vk, false));
				break;
			case TYPE:
				for (auto vk : vks.second) {
					inputs.push_back(makeKeyInput(vk, false));
					inputs.push_back(makeKeyInput(vk, true));
				}
				break;
			case COMBO:
				for (auto vk : vks.second)
					inputs.push_back(makeKeyInput(vk, false));
				for (auto vk : vks.second)
					inputs.push_back(makeKeyInput(vk, true));
				break;
		}
	SendInput(inputs.size(), inputs.data(), sizeof(INPUT));
}

std::pair<LONG, LONG> Utility::screenSize() {
	HWND hwnd = GetDesktopWindow();
	RECT desktop;
	GetWindowRect(hwnd, &desktop);
	return {desktop.right, desktop.bottom};
}

POINT Utility::mousePosition() {
	POINT mousePosition;
	GetCursorPos(&mousePosition);
	return mousePosition;
}

std::string Utility::foregroundTitle() {
	HWND hwnd = GetForegroundWindow();
	char windowTitle[256];
	GetWindowText(hwnd, windowTitle, sizeof(windowTitle));
	return windowTitle;
}

INPUT Utility::makeKeyInput(WORD vk, bool up) {
	INPUT input = {INPUT_KEYBOARD};
	input.ki = {vk, 0, up ? KEYEVENTF_KEYUP : static_cast<DWORD>(0), 0, 0};
	return input;
}
