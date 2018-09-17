#include "Clipboard.h"

std::string Clipboard::getClipboardText() {
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

void Clipboard::sendCtrlC() {
	INPUT ctrlDown = makeKeyInput(VK_CONTROL);
	INPUT cDown = makeKeyInput('C');
	INPUT ctrlUp = makeKeyInput(VK_CONTROL, KEYEVENTF_KEYUP);
	INPUT cUp = makeKeyInput('C', KEYEVENTF_KEYUP);
	INPUT inputs[] = {ctrlDown, cDown, ctrlUp, cUp};
	SendInput(4, inputs, sizeof(INPUT));
}

INPUT Clipboard::makeKeyInput(WORD vk, DWORD flags) {
	INPUT input = {INPUT_KEYBOARD};
	input.ki = {vk, 0, flags, 0, 0};
	return input;
}
