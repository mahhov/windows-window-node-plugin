#include <stdio.h>
#include "../src/Utility.h"

int main() {
	auto mouse = Utility::mousePosition();
	printf("%ld, %ld\n", mouse.first, mouse.second);
}

// g++ -lgdi32 src\Utility.cc test\TestMouse.cc && a.exe
