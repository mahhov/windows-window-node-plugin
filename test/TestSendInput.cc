#include <windows.h>
#include <stdio.h>
#include "../src/Utility.h"

int main() {
	WORD slash = VkKeyScanA('/'); // slash is / 191

	printf("slash %d\n", slash);

	std::vector<std::pair<Utility::SendKeysState, std::vector<WORD>>> vkss = {
		{Utility::SendKeysState::DOWN, {slash}},
		{Utility::SendKeysState::DOWN, {slash}},
		{Utility::SendKeysState::UP, {slash}},
	};

	// printf("wait 1 seconds\n");
	// Sleep(1000);
	// printf("pressing\n");
	Utility::sendKeys(vkss);
	// printf("complete\n");
}

//  g++ -lgdi32 src\Utility.cc test\TestSendInput.cc && a.exe