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

INPUT Utility::makeKeyInput(WORD vk, bool up) {
	INPUT input = {INPUT_KEYBOARD};
	input.ki = {vk, 0, up ? KEYEVENTF_KEYUP : static_cast<DWORD>(0), 0, 0};
	return input;
}
