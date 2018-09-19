#include <windows.h>
#include <stdio.h>

int main() {
	SendMessage(HWND_BROADCAST, WM_COPY, 0, 0);
}

// g++ -lgdi32 test\TestCopy.cc && a.exe