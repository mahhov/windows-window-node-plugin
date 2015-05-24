#include "Window.h"
#include <stdio.h>

const char windowClassName[] = "myWindowClass";

void Window::makeWindow() {
    HINSTANCE hInstance = GetModuleHandle(0);
    WNDCLASSEX windowClass;
    windowClass.cbSize        = sizeof(WNDCLASSEX);
    windowClass.style         = 0;
    windowClass.lpfnWndProc   = process;
    windowClass.cbClsExtra    = 0;
    windowClass.cbWndExtra    = 0;
    windowClass.hInstance     = hInstance;
    windowClass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    windowClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
    windowClass.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    windowClass.lpszMenuName  = NULL;
    windowClass.lpszClassName = windowClassName;
    windowClass.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    RegisterClassEx(&windowClass);

    hwnd = CreateWindowEx(
        WS_EX_APPWINDOW,
        windowClassName,
        NULL,
        WS_POPUP | WS_BORDER,
        0, 0, 0, 0,
        NULL, NULL, hInstance, this);

    UpdateWindow(hwnd);
}

bool Window::update() {
    MSG msg;
    int getMsgStatus = GetMessage(&msg, NULL, 0, 0);
    TranslateMessage(&msg);
    DispatchMessage(&msg);
    return getMsgStatus > 0;
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
    ShowWindow(hwnd, 1);
}

void Window::hide() {
    ShowWindow(hwnd, 0);
}

void Window::setLine(int index, std::string line) {
    lines[index] = line;
    // RedrawWindow(hwnd, NULL, NULL, 0); // todo is this needed
}

void Window::draw(HWND hwnd) {
      PAINTSTRUCT ps;
      HDC hdc = BeginPaint(hwnd, &ps);

      // FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW + 1));
      for(int i = 0; i != lines.size(); i++) { // todo try using lines.size_type
          auto myRect = RECT{0, i * lineHeight, width, (i + 1) * lineHeight};
          LPCSTR text =  lines[i].c_str();
          DrawText(hdc, text, -1, &myRect, 0);
      }

      EndPaint(hwnd, &ps);
}

LRESULT CALLBACK Window::process(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) {
        case WM_NCCREATE:
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR) ((CREATESTRUCT*)lParam)->lpCreateParams);
            return DefWindowProc(hwnd, msg, wParam, lParam);
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_PAINT: {
            Window* window = (Window*) GetWindowLongPtr(hwnd, GWLP_USERDATA);
            window->draw(hwnd);
            break;
        } default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

/*
// --- NAN StUFF ---

Nan::Persistent<v8::FunctionTemplate> Window::constructor;

NAN_MODULE_INIT(Window::nInit) {
    v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Window::nNew);
    constructor.Reset(ctor);
    ctor->InstanceTemplate()->SetInternalFieldCount(1);
    ctor->SetClassName(Nan::New("Window").ToLocalChecked());

    Nan::SetPrototypeMethod(ctor, "new", nNew);
    Nan::SetPrototypeMethod(ctor, "makeWindow", nMakeWindow);
    Nan::SetPrototypeMethod(ctor, "update", nUpdate);
    Nan::SetPrototypeMethod(ctor, "setGeometry", nSetGeometry);
    Nan::SetPrototypeMethod(ctor, "setLines", nSetLines);
    Nan::SetPrototypeMethod(ctor, "show", nShow);
    Nan::SetPrototypeMethod(ctor, "hide", nHide);
    Nan::SetPrototypeMethod(ctor, "setLine", nSetLine);

    target->Set(Nan::New("Window").ToLocalChecked(), ctor->GetFunction());
}

NAN_METHOD(Window::nNew) {
    if(!info.IsConstructCall())
        return Nan::ThrowError(Nan::New("use new keyword").ToLocalChecked());

    if(info.Length() != 0)
        return Nan::ThrowError(Nan::New("window constructor takes 0 arguments").ToLocalChecked());

    Window* window = new Window();
    window->Wrap(info.Holder());
    info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(Window::nMakeWindow) {
    if(info.Length() != 0)
        return Nan::ThrowError(Nan::New("makeWindow requires no arguments").ToLocalChecked());

    Window* self = Nan::ObjectWrap::Unwrap<Window>(info.This());
    self->makeWindow();
}

NAN_METHOD(Window::nUpdate) {
    Window* self = Nan::ObjectWrap::Unwrap<Window>(info.This());
    bool returnValue = self->update();
    info.GetReturnValue().Set(returnValue);
}

NAN_METHOD(Window::nSetGeometry) {
    if(info.Length() != 4 || !info[0]->IsInt32() || !info[1]->IsInt32() || !info[2]->IsInt32() || !info[3]->IsInt32())
        return Nan::ThrowError(Nan::New("setGeometry requires (int x, int y, int width, int height) arguments").ToLocalChecked());

    Window* self = Nan::ObjectWrap::Unwrap<Window>(info.This());
    self->setGeometry(info[0]->Int32Value(), info[1]->Int32Value(), info[2]->Int32Value(), info[3]->Int32Value());
}

NAN_METHOD(Window::nSetLines) {
  if(info.Length() != 2 || !info[0]->IsInt32() || !info[1]->IsInt32())
      return Nan::ThrowError(Nan::New("setLines requires (int lineCount, int lineHeight) arguments").ToLocalChecked());

  Window* self = Nan::ObjectWrap::Unwrap<Window>(info.This());
  self->setLines(info[0]->Int32Value(), info[1]->Int32Value());
}

NAN_METHOD(Window::nShow) {
  if(info.Length() != 0)
      return Nan::ThrowError(Nan::New("show requires no arguments").ToLocalChecked());

    Window* self = Nan::ObjectWrap::Unwrap<Window>(info.This());
    self->show();
}

NAN_METHOD(Window::nHide) {
    if(info.Length() != 0)
        return Nan::ThrowError(Nan::New("hide requires no arguments").ToLocalChecked());

    Window* self = Nan::ObjectWrap::Unwrap<Window>(info.This());
    self->hide();
}

NAN_METHOD(Window::nSetLine) {
    if(info.Length() != 2 || !info[0]->IsInt32() || !info[1]->IsString())
        return Nan::ThrowError(Nan::New("setLines requires (int index, string line) arguments").ToLocalChecked());

    Window* self = Nan::ObjectWrap::Unwrap<Window>(info.This());
    self->setLine(info[0]->Int32Value(), *Nan::Utf8String(info[1]));
}
*/

int main() {
    Window window;
    window.makeWindow();
    window.setGeometry(100, 100, 250, 40);
    window.setLines(2, 20);
    window.show();
    window.setLine(0, "hi there !!");
    window.setLine(1, "this is line 2");
    while (window.update())
        ;
}
