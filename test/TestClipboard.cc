#include <stdio.h>
#include "../src/Clipboard.h"

int main() {
	printf("%s\n", Clipboard::getClipboardText().c_str());
}

// g++ -lgdi32 src\Window.cc test\TestClipboard.cc && a.exe
