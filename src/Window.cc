#include "Window.h"
#include "shellapi.h"

const int WM_TOOLTIP = WM_USER;
const char windowClassName[] = "myWindowClass";

Window::Window(std::string name) : name(std::move(name)) {}

void Window::makeWindow() {
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
	windowClass.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
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

	addSystemTrayIcon();

	hasWindow = true;
}

void Window::destroyWindow() {
	DestroyWindow(hwnd);
}

void Window::setSystemTrayCallback(std::function<void()> callback) {
	systemTrayCallback = std::move(callback);
}

void Window::update() {
	MSG msg;
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void Window::setGeometry(int x, int y, int width, int height) {
	this->width = width;
	MoveWindow(hwnd, x, y, width, height, true);
}

void Window::setLines(int lineCount, int lineHeight) {
	lines.assign(lineCount, "");
	this->lineHeight = lineHeight;
}

void Window::show() {
	visible = true;
	ShowWindow(hwnd, SW_SHOWNORMAL);
	markDrawDirty();
}

void Window::hide() {
	visible = false;
	ShowWindow(hwnd, SW_HIDE);
}

void Window::setLine(int index, std::string line) {
	lines[index] = line;
	markDrawDirty();
}

void Window::addSystemTrayIcon() {
	NOTIFYICONDATA nid;
	nid.uID = 0;
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = hwnd;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = WM_TOOLTIP;
	nid.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	lstrcpy(nid.szTip, name.c_str());
	Shell_NotifyIcon(NIM_ADD, &nid);
}

void Window::markDrawDirty() {
	RedrawWindow(hwnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_UPDATENOW);
}

void Window::draw() {
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);

	for (int i = 0; i != lines.size(); i++) {
		RECT myRect{0, i * lineHeight, width, (i + 1) * lineHeight};
		LPCSTR text = lines[i].c_str();
		DrawText(hdc, text, -1, &myRect, 0);
	}

	EndPaint(hwnd, &ps);
}

LRESULT CALLBACK Window::process(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
		case WM_NCCREATE:
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR) ((CREATESTRUCT*) lParam)->lpCreateParams);
			return DefWindowProc(hwnd, msg, wParam, lParam);
		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;
		case WM_DESTROY: {
			Window* window = (Window*) GetWindowLongPtr(hwnd, GWLP_USERDATA);
			window->hasWindow = false;
			PostQuitMessage(0);
			break;
		}
		case WM_PAINT: {
			Window* window = (Window*) GetWindowLongPtr(hwnd, GWLP_USERDATA);
			window->draw();
			break;
		}
		case WM_TOOLTIP: {
			if (lParam == WM_RBUTTONUP || lParam == WM_MBUTTONUP || lParam == WM_LBUTTONUP) {
				Window* window = (Window*) GetWindowLongPtr(hwnd, GWLP_USERDATA);
				if (window->systemTrayCallback != nullptr)
					window->systemTrayCallback();
			}
			break;
		}
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}
