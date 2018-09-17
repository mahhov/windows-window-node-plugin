#include <nan.h>
#include "Window.h"

class Wrapper : public Nan::ObjectWrap {
  public:
	Wrapper() : window(new Window()) {}

	static NAN_METHOD(Wrapper::nNew) {
		if (!info.IsConstructCall())
			return Nan::ThrowError(Nan::New("use new keyword").ToLocalChecked());

		Wrapper* windowWrap = new Wrapper(); // todo smart pointer?
		windowWrap->Wrap(info.Holder());
		info.GetReturnValue().Set(info.Holder());
	}

	static NAN_METHOD(nMakeWindow) {
		Wrapper* windowWrap = Nan::ObjectWrap::Unwrap<Wrapper>(info.This());
		Window* window = windowWrap->window;
		window->makeWindow();
	}

	static NAN_METHOD(Wrapper::nUpdate) {
		Wrapper* windowWrap = Nan::ObjectWrap::Unwrap<Wrapper>(info.This());
		Window* window = windowWrap->window;
		window->update();
	}

	static NAN_METHOD(Wrapper::nSetGeometry) {
		Wrapper* windowWrap = Nan::ObjectWrap::Unwrap<Wrapper>(info.This());
		Window* window = windowWrap->window;
		window->setGeometry(info[0]->Int32Value(), info[1]->Int32Value(), info[2]->Int32Value(), info[3]->Int32Value());
	}

	static NAN_METHOD(Wrapper::nSetLines) {
		Wrapper* windowWrap = Nan::ObjectWrap::Unwrap<Wrapper>(info.This());
		Window* window = windowWrap->window;
		window->setLines(info[0]->Int32Value(), info[1]->Int32Value());
	}

	static NAN_METHOD(Wrapper::nShow) {
		Wrapper* windowWrap = Nan::ObjectWrap::Unwrap<Wrapper>(info.This());
		Window* window = windowWrap->window;
		window->show();
	}

	static NAN_METHOD(Wrapper::nHide) {
		Wrapper* windowWrap = Nan::ObjectWrap::Unwrap<Wrapper>(info.This());
		Window* window = windowWrap->window;
		window->hide();
	}

	static NAN_METHOD(Wrapper::nSetLine) {
		Wrapper* windowWrap = Nan::ObjectWrap::Unwrap<Wrapper>(info.This());
		Window* window = windowWrap->window;
		window->setLine(info[0]->Int32Value(), *Nan::Utf8String(info[1]));
	}

	static NAN_GETTER(Wrapper::nHasWindow) {
		Wrapper* windowWrap = Nan::ObjectWrap::Unwrap<Wrapper>(info.This());
		Window* window = windowWrap->window;
		info.GetReturnValue().Set(window->hasWindow);
	}

	static NAN_MODULE_INIT(Wrapper::nInit) {
		v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Wrapper::nNew);
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
		Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("hasWindow").ToLocalChecked(), nHasWindow);

		target->Set(Nan::New("Window").ToLocalChecked(), ctor->GetFunction());
	}

	Window* window;
	static Nan::Persistent<v8::FunctionTemplate> constructor;
};

Nan::Persistent<v8::FunctionTemplate> Wrapper::constructor; // todo how to avoid this

NAN_MODULE_INIT(InitModule) {
	Wrapper::nInit(target);
}

NODE_MODULE(myModule, InitModule
);
