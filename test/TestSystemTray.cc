#include <stdio.h>
#include "../src/Window.h"

int main() {
	Window window;
	window.makeWindow();

	while (window.hasWindow)
		window.update();
}

// g++ -lgdi32 src\Window.cc test\TestSystemTray.cc && a.exe
