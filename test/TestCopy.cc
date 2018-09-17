#include <windows.h>
#include <stdio.h>

int main() {
	SendMessage(HWND_BROADCAST, WM_COPY, 0, 0);
}