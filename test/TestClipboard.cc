#include "../src/Window.h"

std::string GetClipboardText() {
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

int main() {
	Window window;
	window.makeWindow();
	window.setGeometry(100, 100, 250, 40);
	window.setLines(2, 20);
	window.show();
	window.setLine(0, "hi there !!");
	window.setLine(1, "this is line 2");

	int i = 0;
	while (window.hasWindow) {
		window.setLine(1, std::to_string(i++));
		window.update();
	}

	printf("%s\n", GetClipboardText().c_str());
}

// g++ -lgdi32 src\Window.cc test\TestClipboard.cc && a.exe
