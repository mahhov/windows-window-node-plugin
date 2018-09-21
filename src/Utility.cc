#include "Utility.h"

std::string Utility::getClipboardText() {
	// https://stackoverflow.com/a/14763025/6951428
	if (!OpenClipboard(nullptr))
		return "";
	HANDLE hData = GetClipboardData(CF_TEXT);
	if (hData == nullptr)
		return "";
	char* pszText = static_cast<char*>( GlobalLock(hData));
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

void Utility::sendKeys(std::vector<std::vector<WORD>> vkss) {
	std::vector<INPUT> inputs;
	bool up = true;
	for (auto vks : vkss) {
		for (auto vk : vks)
			inputs.push_back(makeKeyInput(vk, up));
		up = !up;
	}
	SendInput(inputs.size(), inputs.data(), sizeof(INPUT));
}

std::pair<LONG, LONG> Utility::screenSize() {
	HWND hDesktop = GetDesktopWindow();
	RECT desktop;
	GetWindowRect(hDesktop, &desktop);
	return {desktop.right, desktop.bottom};
}

POINT Utility::mousePosition() {
	POINT mousePosition;
	GetCursorPos(&mousePosition);
	return mousePosition;
}

INPUT Utility::makeKeyInput(WORD vk, bool up) {
	INPUT input = {INPUT_KEYBOARD};
	input.ki = {vk, 0, up ? KEYEVENTF_KEYUP : static_cast<DWORD>(0), 0, 0};
	return input;
}
