#include <windows.h>
#include <stdio.h>
#include "../src/Utility.h"

int main() {
	std::vector<std::vector<WORD>> vkss = {{}, {'C'}, {'C'}};

	// printf("wait 1 seconds\n");
	// Sleep(1000);
	// printf("pressing\n");
	Utility::sendKeys(vkss);
	// printf("complete\n");
}

//  g++ -lgdi32 src\Utility.cc test\TestSendInput.cc && a.exe