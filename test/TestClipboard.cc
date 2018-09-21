#include <stdio.h>
#include "../src/Utility.h"

int main() {
	printf("%s\n", Clipboard::getClipboardText().c_str());
}

// g++ -lgdi32 src\Utility.cc test\TestClipboard.cc && a.exe
