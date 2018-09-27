#include <stdio.h>
#include <Windows.h>
#include "../src/Utility.h"

int main() {
	if (RegisterHotKey(
		NULL,
		1,
		MOD_CONTROL | MOD_SHIFT,//MOD_ALT,//| MOD_NOREPEAT,
		0x43))  //0x42 is 'b'
	{
		printf("Hotkey 'ALT+b' registered, using MOD_NOREPEAT flag\n");
	}

	MSG msg = {0};
	while (GetMessage(&msg, NULL, 0, 0) != 0) {
		if (msg.message == WM_HOTKEY) {
			std::vector<std::pair<Utility::SendKeysState, std::vector<WORD>>> vkss = {
				{Utility::SendKeysState::DOWN, {VK_CONTROL, VkKeyScanA('C')}},
				{Utility::SendKeysState::UP,   {VkKeyScanA('C'), VK_CONTROL}},
				{Utility::SendKeysState::DOWN, {VK_CONTROL, VkKeyScanA('V')}},
				{Utility::SendKeysState::UP,   {VkKeyScanA('V'), VK_CONTROL}},
				{Utility::SendKeysState::DOWN, {VK_CONTROL, VkKeyScanA('V')}},
				{Utility::SendKeysState::UP,   {VkKeyScanA('V'), VK_CONTROL}},
			};
			Utility::sendKeys(vkss);
		}
	}
}

// g++ -lgdi32 test\TestHotkey.cc src\Utility.cc && a.exe
