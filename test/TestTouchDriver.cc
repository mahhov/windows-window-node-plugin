#define _WIN32_WINNT 0x0602

#include <stdio.h>
#include <Windows.h>
#include <string>
#include <vector>
#include <functional>
#include <shellapi.h>

const char windowClassName[] = "myWindowClass";

class X {
  public:
	HWND hwnd;

	void makeWindow() {
		HINSTANCE hInstance = GetModuleHandle(0);
		WNDCLASSEX windowClass;
		windowClass.cbSize = sizeof(WNDCLASSEX);
		windowClass.style = 0;
		windowClass.lpfnWndProc = process;
		windowClass.cbClsExtra = 0;
		windowClass.cbWndExtra = 0;
		windowClass.hInstance = hInstance;
		windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		windowClass.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1); // todo proper casting
		windowClass.lpszMenuName = NULL;
		windowClass.lpszClassName = windowClassName;
		windowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		RegisterClassEx(&windowClass);

		hwnd = CreateWindowEx(
			WS_EX_NOACTIVATE | WS_EX_TOPMOST,
			windowClassName,
			NULL,
			WS_POPUP | WS_BORDER,
			0, 0, 0, 0,
			NULL, NULL, hInstance, this);
	}

	void destroyWindow() {
		DestroyWindow(hwnd);
	}

	void update() {
		MSG msg;
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	static LRESULT CALLBACK process(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		switch (msg) {
			case 0x00FF: // WM_INPUT:
				printf("RECIEVED INPUT\n");
				return DefWindowProc(hwnd, msg, wParam, lParam);
			default:
				return
					DefWindowProc(hwnd, msg, wParam, lParam);
		}
		return 0;
	}
};

int main() {
	UINT nDevices;
	PRAWINPUTDEVICELIST pRawInputDeviceList;
	if (GetRawInputDeviceList(NULL, &nDevices, sizeof(RAWINPUTDEVICELIST)) != 0)
		printf("error 1\n");
	if ((pRawInputDeviceList = (PRAWINPUTDEVICELIST) malloc(sizeof(RAWINPUTDEVICELIST) * nDevices)) == NULL)
		printf("error 2\n");
	if (GetRawInputDeviceList(pRawInputDeviceList, &nDevices, sizeof(RAWINPUTDEVICELIST)) == -1)
		printf("error 3\n");
	printf("%d\n", nDevices);
	free(pRawInputDeviceList);

//	RAWINPUTDEVICE Rid[1];
//
//	Rid[0].usUsagePage = 0x01;
//	Rid[0].usUsage = 0x05;
//	Rid[0].dwFlags = 0;
//	Rid[0].hwndTarget = 0;
//	if (RegisterRawInputDevices(Rid, 1, sizeof(Rid[0])) == FALSE)
//		printf("failed to register\n");

//	X window;
//	window.makeWindow();
//	while (true)
//		window.update();
}

// g++ -lgdi32 test\TestTouchDriver.cc && a.exe
