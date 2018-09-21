#include "wtypes.h"
#include <iostream>

#include "../src/Utility.h"

int main() {
	auto x = Utility::screenSize();
	printf("%d, %d\n", x.first, x.second);
	return 0;
}

// g++ -lgdi32 src\Utility.cc test\TestScreenSize.cc && a.exe
