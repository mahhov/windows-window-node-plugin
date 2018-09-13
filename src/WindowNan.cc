#include <nan.h>
#include "Window.h"

class WindowWrap : public Nan::ObjectWrap {
  public:
	WindowWrap() : window(new Window()) {}

	static NAN_METHOD(WindowWrap::nNew) {
		if (!info.IsConstructCall())
			return Nan::ThrowError(Nan::New("use new keyword").ToLocalChecked());

		WindowWrap* windowWrap = new WindowWrap(); // todo smart pointer?
		windowWrap->Wrap(info.Holder());
		info.GetReturnValue().Set(info.Holder());
	}

	static NAN_METHOD(nMakeWindow) {
		WindowWrap* windowWrap = Nan::ObjectWrap::Unwrap<WindowWrap>(info.This());
		Window* window = windowWrap->window;
		window->makeWindow();
	}

	static NAN_METHOD(WindowWrap::nUpdate) {
		WindowWrap* windowWrap = Nan::ObjectWrap::Unwrap<WindowWrap>(info.This());
		Window* window = windowWrap->window;
		window->update();
	}

	static NAN_METHOD(WindowWrap::nSetGeometry) {
		WindowWrap* windowWrap = Nan::ObjectWrap::Unwrap<WindowWrap>(info.This());
		Window* window = windowWrap->window;
		window->setGeometry(info[0]->Int32Value(), info[1]->Int32Value(), info[2]->Int32Value(), info[3]->Int32Value());
	}

	static NAN_METHOD(WindowWrap::nSetLines) {
		WindowWrap* windowWrap = Nan::ObjectWrap::Unwrap<WindowWrap>(info.This());
		Window* window = windowWrap->window;
		window->setLines(info[0]->Int32Value(), info[1]->Int32Value());
	}

	static NAN_METHOD(WindowWrap::nShow) {
		WindowWrap* windowWrap = Nan::ObjectWrap::Unwrap<WindowWrap>(info.This());
		Window* window = windowWrap->window;
		window->show();
	}

	static NAN_METHOD(WindowWrap::nHide) {
		WindowWrap* windowWrap = Nan::ObjectWrap::Unwrap<WindowWrap>(info.This());
		Window* window = windowWrap->window;
		window->hide();
	}

	static NAN_METHOD(WindowWrap::nSetLine) {
		WindowWrap* windowWrap = Nan::ObjectWrap::Unwrap<WindowWrap>(info.This());
		Window* window = windowWrap->window;
		window->setLine(info[0]->Int32Value(), *Nan::Utf8String(info[1]));
	}

	static NAN_MODULE_INIT(WindowWrap::nInit) {
		v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(WindowWrap::nNew);
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
