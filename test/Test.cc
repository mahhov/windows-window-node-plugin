#include "../src/Window.h"
#include <string>

int main() {
	Window window("Test.cc");

	auto callback = []() {
		printf("CLICK ME\n");
	};
	window.setSystemTrayCallback(callback);

	window.makeWindow();
	window.setGeometry(100, 100, 250, 40);
	window.setLines(2, 20);
	window.show();
	window.setLine(0, "hi there !!");
	window.setLine(1, "this is line 2");

	int i = 0;
	while (window.hasWindow) {
		// window.setLine(1, std::to_string(i++));
		window.update();
	}
}

// g++ -lgdi32 src\Window.cc test\Test.cc && a.exe
