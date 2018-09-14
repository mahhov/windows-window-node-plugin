#include "Window"

int main() {
	Window window;
	window.makeWindow();
	window.setGeometry(100, 100, 250, 40);
	window.setLines(2, 20);
	window.show();
	window.setLine(0, "hi there !!");
	window.setLine(1, "this is line 2");

	int i = 0;
	while (window.update())
		window.setLine(1, std::to_string(i++));
}
