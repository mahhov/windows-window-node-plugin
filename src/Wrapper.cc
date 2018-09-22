#include <nan.h>
#include <windows.h>
#include "Window.h"
#include "Utility.h"

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

	static NAN_GETTER(Wrapper::nVisible) {
		Wrapper* windowWrap = Nan::ObjectWrap::Unwrap<Wrapper>(info.This());
		Window* window = windowWrap->window;
		info.GetReturnValue().Set(window->visible);
	}

	static NAN_GETTER(Wrapper::nHasWindow) {
		Wrapper* windowWrap = Nan::ObjectWrap::Unwrap<Wrapper>(info.This());
		Window* window = windowWrap->window;
		info.GetReturnValue().Set(window->hasWindow);
	}

	static NAN_METHOD(Wrapper::nGetClipboardText) {
		std::string clipboardText = Utility::getClipboardText();
		info.GetReturnValue().Set(Nan::New(clipboardText).ToLocalChecked());
	}

	static NAN_METHOD(Wrapper::nSetClipboardText) {
		Utility::setClipboardText(*Nan::Utf8String(info[0]));
	}

	static NAN_METHOD(Wrapper::nClearClipboardText) {
		Utility::clearClipboardText();
	}

	static NAN_METHOD(Wrapper::nSendKeys) {
		std::vector<std::vector<WORD>> keys;
		v8::Local<v8::Array> inputs = v8::Local<v8::Array>::Cast(info[0]);
		for (unsigned int i = 0; i < inputs->Length(); i++) {
			std::vector<WORD> keysInner;
			v8::Local<v8::Array> inner = v8::Local<v8::Array>::Cast(inputs->Get(i));
			for (unsigned int j = 0; j < inner->Length(); j++)
				keysInner.push_back(static_cast<WORD>(inner->Get(j)->Int32Value()));
			keys.push_back(keysInner);
		}
		Utility::sendKeys(keys);
	}

	static NAN_METHOD(Wrapper::nScreenSize) {
		std::pair<LONG, LONG> mouse = Utility::screenSize();
		v8::Local<v8::Array> outputs = Nan::New<v8::Array>(2);
		outputs->Set(0, Nan::New((int) mouse.first)); // todo use correct cast + why do we need cast?
		outputs->Set(1, Nan::New((int) mouse.second));
		info.GetReturnValue().Set(outputs);
	}

	static NAN_METHOD(Wrapper::nMousePosition) {
		POINT mouse = Utility::mousePosition();
		v8::Local<v8::Array> outputs = Nan::New<v8::Array>(2);
		outputs->Set(0, Nan::New((int) mouse.x)); // todo use correct cast + why do we need cast?
		outputs->Set(1, Nan::New((int) mouse.y));
		info.GetReturnValue().Set(outputs);
	}

	static NAN_METHOD(Wrapper::nForegroundTitle) {
		std::string title = Utility::foregroundTitle();
		info.GetReturnValue().Set(Nan::New(title).ToLocalChecked());
	}

	static NAN_MODULE_INIT(Wrapper::nInit) {
		v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Wrapper::nNew);
		constructor.Reset(ctor);
		ctor->InstanceTemplate()->SetInternalFieldCount(1);
		ctor->SetClassName(Nan::New("Window").ToLocalChecked());

		// window
		Nan::SetPrototypeMethod(ctor, "new", nNew);
		Nan::SetPrototypeMethod(ctor, "makeWindow", nMakeWindow);
		Nan::SetPrototypeMethod(ctor, "update", nUpdate);
		Nan::SetPrototypeMethod(ctor, "setGeometry", nSetGeometry);
		Nan::SetPrototypeMethod(ctor, "setLines", nSetLines);
		Nan::SetPrototypeMethod(ctor, "show", nShow);
		Nan::SetPrototypeMethod(ctor, "hide", nHide);
		Nan::SetPrototypeMethod(ctor, "setLine", nSetLine);
		Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("visible").ToLocalChecked(), nVisible);
		Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("hasWindow").ToLocalChecked(), nHasWindow);

		// utility
		Nan::SetMethod(ctor, "getClipboardText", nGetClipboardText);
		Nan::SetMethod(ctor, "setClipboardText", nSetClipboardText);
		Nan::SetMethod(ctor, "clearClipboardText", nClearClipboardText);
		Nan::SetMethod(ctor, "sendKeys", nSendKeys);
		Nan::SetMethod(ctor, "screenSize", nScreenSize);
		Nan::SetMethod(ctor, "mousePosition", nMousePosition);
		Nan::SetMethod(ctor, "foregroundTitle", nForegroundTitle);

		target->Set(Nan::New("Window").ToLocalChecked(), ctor->GetFunction());
	}

	Window* window;
	static Nan::Persistent<v8::FunctionTemplate> constructor;
};

Nan::Persistent<v8::FunctionTemplate> Wrapper::constructor; // todo how to avoid this

NAN_MODULE_INIT(InitModule) {
	Wrapper::nInit(target);
}

NODE_MODULE(myModule, InitModule);
