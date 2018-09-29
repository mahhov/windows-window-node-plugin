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
	window->makeWindow();
}

NAN_METHOD(WindowWrapper::windowDestroyWindow) {
	auto* windowWrapper = Nan::ObjectWrap::Unwrap<WindowWrapper>(info.This());
	Window* window = windowWrapper->window;
	window->destroyWindow();
}

NAN_METHOD(WindowWrapper::windowSetSystemTrayCallback) {
	auto* windowWrapper = Nan::ObjectWrap::Unwrap<WindowWrapper>(info.This());
	windowWrapper->systemTrayCallback.Reset(info[0].As<v8::Function>());

	std::function<void()> callback = [windowWrapper]() {
		Nan::Call(windowWrapper->systemTrayCallback, 0, nullptr);
	};

	Window* window = windowWrapper->window;
	window->setSystemTrayCallback(callback);
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
