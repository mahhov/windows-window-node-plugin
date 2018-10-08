#include "WindowWrapper.h"

Nan::Persistent<v8::FunctionTemplate> WindowWrapper::constructor;

NAN_MODULE_INIT(WindowWrapper::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(WindowWrapper::windowNew);
	constructor.Reset(ctor);
	ctor->InstanceTemplate()->SetInternalFieldCount(1);
	ctor->SetClassName(Nan::New("Window").ToLocalChecked());

	Nan::SetPrototypeMethod(ctor, "makeWindow", windowMakeWindow);
	Nan::SetPrototypeMethod(ctor, "destroyWindow", windowDestroyWindow);
	Nan::SetPrototypeMethod(ctor, "setSystemTrayCallback", windowSetSystemTrayCallback);
	Nan::SetPrototypeMethod(ctor, "setClipboardCallback", windowSetClipboardCallback);
	Nan::SetPrototypeMethod(ctor, "setFocusCallback", windowSetFocusCallback);
	Nan::SetPrototypeMethod(ctor, "setKeyCallback", windowSetKeyCallback);
	Nan::SetPrototypeMethod(ctor, "update", windowUpdate);
	Nan::SetPrototypeMethod(ctor, "setGeometry", windowSetGeometry);
	Nan::SetPrototypeMethod(ctor, "setLines", windowSetLines);
	Nan::SetPrototypeMethod(ctor, "show", windowShow);
	Nan::SetPrototypeMethod(ctor, "hide", windowHide);
	Nan::SetPrototypeMethod(ctor, "setLine", windowSetLine);
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("visible").ToLocalChecked(), windowVisible);
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("hasWindow").ToLocalChecked(), windowHasWindow);

	target->Set(Nan::New("Window").ToLocalChecked(), ctor->GetFunction());
}

NAN_METHOD(WindowWrapper::windowNew) {
	if (!info.IsConstructCall())
		return Nan::ThrowError(Nan::New("use new keyword").ToLocalChecked());

	auto* windowWrapper = new WindowWrapper(); // todo smart pointer?
	windowWrapper->window = new Window(*Nan::Utf8String(info[0]));
	windowWrapper->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(WindowWrapper::windowMakeWindow) {
	auto* windowWrapper = Nan::ObjectWrap::Unwrap<WindowWrapper>(info.This());
	Window* window = windowWrapper->window;
	window->makeWindow(info[0]->BooleanValue());
}

NAN_METHOD(WindowWrapper::windowDestroyWindow) {
	auto* windowWrapper = Nan::ObjectWrap::Unwrap<WindowWrapper>(info.This());
	Window* window = windowWrapper->window;
	window->destroyWindow();
}

NAN_METHOD(WindowWrapper::windowSetSystemTrayCallback) {
	auto* windowWrapper = Nan::ObjectWrap::Unwrap<WindowWrapper>(info.This());
	windowWrapper->systemTrayCallback.Reset(info[0].As<v8::Function>());

	auto callback = [windowWrapper]() {
		Nan::Call(windowWrapper->systemTrayCallback, 0, nullptr);
	};

	Window* window = windowWrapper->window;
	window->setSystemTrayCallback(callback);
}

NAN_METHOD(WindowWrapper::windowSetClipboardCallback) {
	auto* windowWrapper = Nan::ObjectWrap::Unwrap<WindowWrapper>(info.This());
	windowWrapper->clipboardCallback.Reset(info[0].As<v8::Function>());

	auto callback = [windowWrapper](std::string text) {
		v8::Local<v8::Value> args[] {Nan::New(text).ToLocalChecked()};
		Nan::Call(windowWrapper->clipboardCallback, 1, args);
	};

	Window* window = windowWrapper->window;
	window->setClipboardCallback(callback);
}

NAN_METHOD(WindowWrapper::windowSetFocusCallback) {
	auto* windowWrapper = Nan::ObjectWrap::Unwrap<WindowWrapper>(info.This());
	windowWrapper->focusCallback.Reset(info[0].As<v8::Function>());

	auto callback = [windowWrapper](bool focus) {
		v8::Local<v8::Value> args[] {Nan::New(focus)};
		Nan::Call(windowWrapper->focusCallback, 1, args);
	};

	Window* window = windowWrapper->window;
	window->setFocusCallback(callback);
}

NAN_METHOD(WindowWrapper::windowSetKeyCallback) {
	auto* windowWrapper = Nan::ObjectWrap::Unwrap<WindowWrapper>(info.This());
	windowWrapper->keyCallback.Reset(info[0].As<v8::Function>());

	auto callback = [windowWrapper](int key) {
		v8::Local<v8::Value> args[] {Nan::New(key)};
		Nan::Call(windowWrapper->keyCallback, 1, args);
	};

	Window* window = windowWrapper->window;
	window->setKeyCallback(callback);
}

NAN_METHOD(WindowWrapper::windowUpdate) {
	auto* windowWrapper = Nan::ObjectWrap::Unwrap<WindowWrapper>(info.This());
	Window* window = windowWrapper->window;
	window->update();
}

NAN_METHOD(WindowWrapper::windowSetGeometry) {
	auto* windowWrapper = Nan::ObjectWrap::Unwrap<WindowWrapper>(info.This());
	Window* window = windowWrapper->window;
	window->setGeometry(info[0]->Int32Value(), info[1]->Int32Value(), info[2]->Int32Value(), info[3]->Int32Value());
}

NAN_METHOD(WindowWrapper::windowSetLines) {
	auto* windowWrapper = Nan::ObjectWrap::Unwrap<WindowWrapper>(info.This());
	Window* window = windowWrapper->window;
	window->setLines(info[0]->Int32Value(), info[1]->Int32Value());
}

NAN_METHOD(WindowWrapper::windowShow) {
	auto* windowWrapper = Nan::ObjectWrap::Unwrap<WindowWrapper>(info.This());
	Window* window = windowWrapper->window;
	window->show();
}

NAN_METHOD(WindowWrapper::windowHide) {
	auto* windowWrapper = Nan::ObjectWrap::Unwrap<WindowWrapper>(info.This());
	Window* window = windowWrapper->window;
	window->hide();
}

NAN_METHOD(WindowWrapper::windowSetLine) {
	auto* windowWrapper = Nan::ObjectWrap::Unwrap<WindowWrapper>(info.This());
	Window* window = windowWrapper->window;
	if (info.Length() >= 4)
		window->setLine(info[0]->Int32Value(), *Nan::Utf8String(info[1]),
		                rgbArrayToColorref(info[2].As<v8::Array>()),
		                rgbArrayToColorref(info[3].As<v8::Array>()));
	else if (info.Length() == 3)
		window->setLine(info[0]->Int32Value(), *Nan::Utf8String(info[1]),
		                rgbArrayToColorref(info[2].As<v8::Array>()));
	else
		window->setLine(info[0]->Int32Value(), *Nan::Utf8String(info[1]));
}

NAN_GETTER(WindowWrapper::windowVisible) {
	auto* windowWrapper = Nan::ObjectWrap::Unwrap<WindowWrapper>(info.This());
	Window* window = windowWrapper->window;
	info.GetReturnValue().Set(window->visible);
}

NAN_GETTER(WindowWrapper::windowHasWindow) {
	auto* windowWrapper = Nan::ObjectWrap::Unwrap<WindowWrapper>(info.This());
	Window* window = windowWrapper->window;
	info.GetReturnValue().Set(window->hasWindow);
}

COLORREF WindowWrapper::rgbArrayToColorref(v8::Local<v8::Array> rgbArray) {
	int r = rgbArray->Get(0)->Int32Value();
	int g = rgbArray->Get(1)->Int32Value();
	int b = rgbArray->Get(2)->Int32Value();
	return RGB(r, g, b);
}
