#include <stdio.h>
#include "../src/Utility.h"

int main() {
	// printf("%s\n", Utility::getClipboardText().c_str());
	Utility::setClipboardText("hi there bruh");
}

// g++ -lgdi32 src\Utility.cc test\TestClipboard.cc && a.exe
