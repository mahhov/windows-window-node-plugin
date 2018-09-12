#include <nan.h>
#include "Window.h"

class WindowWrap : public Nan::ObjectWrap {
  public:
	WindowWrap() : window(new Window()) {}

	static NAN_METHOD(WindowWrap::nNew) {
		if (!info.IsConstructCall())
			return Nan::ThrowError(Nan::New("use new keyword").ToLocalChecked());

		if (info.Length() != 0)
			return Nan::ThrowError(Nan::New("window constructor takes 0 arguments").ToLocalChecked());

		WindowWrap* windowWrap = new WindowWrap(); // todo smart pointer?
		windowWrap->Wrap(info.Holder());
		info.GetReturnValue().Set(info.Holder());
	}

	static NAN_METHOD(nMakeWindow) {
		if (info.Length() != 0)
			return Nan::ThrowError(Nan::New("makeWindow requires no arguments").ToLocalChecked());

		WindowWrap* windowWrap = Nan::ObjectWrap::Unwrap<WindowWrap>(info.This());
		Window* window = windowWrap->window;
		window->makeWindow();
	}

	static NAN_METHOD(WindowWrap::nUpdate) {
		WindowWrap* windowWrap = Nan::ObjectWrap::Unwrap<WindowWrap>(info.This());
		Window* window = windowWrap->window;
		bool returnValue = window->update();
		info.GetReturnValue().Set(returnValue);
	}

	static NAN_METHOD(WindowWrap::nSetGeometry) {
		if (info.Length() != 4 || !info[0]->IsInt32() || !info[1]->IsInt32() || !info[2]->IsInt32() || !info[3]->IsInt32())
			return Nan::ThrowError(Nan::New("setGeometry requires (int x, int y, int width, int height) arguments").ToLocalChecked());

		WindowWrap* windowWrap = Nan::ObjectWrap::Unwrap<WindowWrap>(info.This());
		Window* window = windowWrap->window;
		window->setGeometry(info[0]->Int32Value(), info[1]->Int32Value(), info[2]->Int32Value(), info[3]->Int32Value());
	}

	static NAN_METHOD(WindowWrap::nSetLines) {
		if (info.Length() != 2 || !info[0]->IsInt32() || !info[1]->IsInt32())
			return Nan::ThrowError(Nan::New("setLines requires (int lineCount, int lineHeight) arguments").ToLocalChecked());

		WindowWrap* windowWrap = Nan::ObjectWrap::Unwrap<WindowWrap>(info.This());
		Window* window = windowWrap->window;
		window->setLines(info[0]->Int32Value(), info[1]->Int32Value());
	}

	static NAN_METHOD(WindowWrap::nShow) {
		if (info.Length() != 0)
			return Nan::ThrowError(Nan::New("show requires no arguments").ToLocalChecked());

		WindowWrap* windowWrap = Nan::ObjectWrap::Unwrap<WindowWrap>(info.This());
		Window* window = windowWrap->window;
		window->show();
	}

	static NAN_METHOD(WindowWrap::nHide) {
		if (info.Length() != 0)
			return Nan::ThrowError(Nan::New("hide requires no arguments").ToLocalChecked());

		WindowWrap* windowWrap = Nan::ObjectWrap::Unwrap<WindowWrap>(info.This());
		Window* window = windowWrap->window;
		window->hide();
	}

	static NAN_METHOD(WindowWrap::nSetLine) {
		if (info.Length() != 2 || !info[0]->IsInt32() || !info[1]->IsString())
			return Nan::ThrowError(Nan::New("setLines requires (int index, string line) arguments").ToLocalChecked());

		WindowWrap* windowWrap = Nan::ObjectWrap::Unwrap<WindowWrap>(info.This());
		Window* window = windowWrap->window;
		window->setLine(info[0]->Int32Value(), *Nan::Utf8String(info[1]));
	}

	static NAN_MODULE_INIT(WindowWrap::nInit) {
		v8::Local <v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(WindowWrap::nNew);
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

	Window* window;
	static Nan::Persistent<v8::FunctionTemplate> constructor;
};

Nan::Persistent<v8::FunctionTemplate> WindowWrap::constructor; // todo how to avoid this

NAN_MODULE_INIT(InitModule) {
	WindowWrap::nInit(target);
}

NODE_MODULE(myModule, InitModule
);
