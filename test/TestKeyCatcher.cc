#include <stdio.h>
#include <Windows.h>
#include "../src/Utility.h"
#include "../src/KeyCatcher.h"
#include <windows.h>

int main() {
	KeyCatcher keyCatcher;

	std::function<bool(bool down, int code)> callback = [](bool down, int code) {
		printf("%d %d\n", down, code);
		return false;
	};

	keyCatcher.setCallback(callback);

	keyCatcher.begin();

	printf("ready\n");

	while (true) {
		keyCatcher.update();
		// printf("in loop\n");
		// Sleep(1000);
	}
}

// g++ -lgdi32 test\TestKeyCatcher.cc src\KeyCatcher.cc src\Utility.cc && a.exe
