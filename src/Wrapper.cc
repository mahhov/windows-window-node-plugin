#include <nan.h>
#include <windows.h>
#include "Window.h"
#include "Utility.h"

class Wrapper : public Nan::ObjectWrap {
  public:
	Wrapper() {}

	static NAN_METHOD(Wrapper::nNew) {
		if (!info.IsConstructCall())
			return Nan::ThrowError(Nan::New("use new keyword").ToLocalChecked());

		Wrapper* wrapper = new Wrapper(); // todo smart pointer?
		wrapper->window = new Window(*Nan::Utf8String(info[0]));
		wrapper->Wrap(info.Holder());
		info.GetReturnValue().Set(info.Holder());
	}

	static NAN_METHOD(nMakeWindow) {
		Wrapper* wrapper = Nan::ObjectWrap::Unwrap<Wrapper>(info.This());
		Window* window = wrapper->window;
		window->makeWindow();
	}

	static NAN_METHOD(nDestroyWindow) {
		Wrapper* wrapper = Nan::ObjectWrap::Unwrap<Wrapper>(info.This());
		Window* window = wrapper->window;
		window->destroyWindow();
	}

	static NAN_METHOD(nSetSystemTrayCallback) {
		Wrapper* wrapper = Nan::ObjectWrap::Unwrap<Wrapper>(info.This());
		wrapper->systemTrayCallback.Reset(info[0].As<v8::Function>());
		std::function<void()> callback = [wrapper]() {
			Nan::Call(wrapper->systemTrayCallback, 0, nullptr);
		};

		Window* window = wrapper->window;
		window->setSystemTrayCallback(callback);
	}

	static NAN_METHOD(Wrapper::nUpdate) {
		Wrapper* wrapper = Nan::ObjectWrap::Unwrap<Wrapper>(info.This());
		Window* window = wrapper->window;
		window->update();
	}

	static NAN_METHOD(Wrapper::nSetGeometry) {
		Wrapper* wrapper = Nan::ObjectWrap::Unwrap<Wrapper>(info.This());
		Window* window = wrapper->window;
		window->setGeometry(info[0]->Int32Value(), info[1]->Int32Value(), info[2]->Int32Value(), info[3]->Int32Value());
	}

	static NAN_METHOD(Wrapper::nSetLines) {
		Wrapper* wrapper = Nan::ObjectWrap::Unwrap<Wrapper>(info.This());
		Window* window = wrapper->window;
		window->setLines(info[0]->Int32Value(), info[1]->Int32Value());
	}

	static NAN_METHOD(Wrapper::nShow) {
		Wrapper* wrapper = Nan::ObjectWrap::Unwrap<Wrapper>(info.This());
		Window* window = wrapper->window;
		window->show();
	}

	static NAN_METHOD(Wrapper::nHide) {
		Wrapper* wrapper = Nan::ObjectWrap::Unwrap<Wrapper>(info.This());
		Window* window = wrapper->window;
		window->hide();
	}

	static NAN_METHOD(Wrapper::nSetLine) {
		Wrapper* wrapper = Nan::ObjectWrap::Unwrap<Wrapper>(info.This());
		Window* window = wrapper->window;
		window->setLine(info[0]->Int32Value(), *Nan::Utf8String(info[1]));
	}

	static NAN_GETTER(Wrapper::nVisible) {
		Wrapper* wrapper = Nan::ObjectWrap::Unwrap<Wrapper>(info.This());
		Window* window = wrapper->window;
		info.GetReturnValue().Set(window->visible);
	}

	static NAN_GETTER(Wrapper::nHasWindow) {
		Wrapper* wrapper = Nan::ObjectWrap::Unwrap<Wrapper>(info.This());
		Window* window = wrapper->window;
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
		std::vector<std::pair<Utility::SendKeysState, std::vector<WORD>>> sendKeys;
		v8::Local<v8::Array> inputs = info[0].As<v8::Array>();
		for (unsigned int i = 0; i < inputs->Length(); i++) {
			v8::Local<v8::Array> input = inputs->Get(i).As<v8::Array>();
			auto state = static_cast<Utility::SendKeysState>(input->Get(0)->Int32Value());
			v8::Local<v8::Array> inputKeys = input->Get(1).As<v8::Array>();
			std::vector<WORD> keys;
			for (unsigned int j = 0; j < inputKeys->Length(); j++)
				keys.push_back(static_cast<WORD>(inputKeys->Get(j)->Int32Value()));
			sendKeys.push_back({state, keys});
		}
		Utility::sendKeys(sendKeys);
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
		Nan::SetPrototypeMethod(ctor, "destroyWindow", nDestroyWindow);
		Nan::SetPrototypeMethod(ctor, "setSystemTrayCallback", nSetSystemTrayCallback);
		Nan::SetPrototypeMethod(ctor, "update", nUpdate);
		Nan::SetPrototypeMethod(ctor, "setGeometry", nSetGeometry);
		Nan::SetPrototypeMethod(ctor, "setLines", nSetLines);
		Nan::SetPrototypeMethod(ctor, "show", nShow);
		Nan::SetPrototypeMethod(ctor, "hide", nHide);
		Nan::SetPrototypeMethod(ctor, "setLine", nSetLine);
		Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("visible").ToLocalChecked(), nVisible);
		Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("hasWindow").ToLocalChecked(), nHasWindow);

		// key catcher


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
	Nan::Callback systemTrayCallback;
	static Nan::Persistent<v8::FunctionTemplate> constructor;
};

Nan::Persistent<v8::FunctionTemplate> Wrapper::constructor; // todo how to avoid this

NAN_MODULE_INIT(InitModule) {
	Wrapper::nInit(target);
}

NODE_MODULE(myModule, InitModule);
