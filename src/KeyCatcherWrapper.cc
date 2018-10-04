#include "KeyCatcherWrapper.h"

Nan::Persistent<v8::FunctionTemplate> KeyCatcherWrapper::constructor;

NAN_MODULE_INIT(KeyCatcherWrapper::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(KeyCatcherWrapper::keyCatcherNew);
	constructor.Reset(ctor);
	ctor->InstanceTemplate()->SetInternalFieldCount(1);
	ctor->SetClassName(Nan::New("KeyCatcher").ToLocalChecked());

	Nan::SetPrototypeMethod(ctor, "begin", keyCatcherBegin);
	Nan::SetPrototypeMethod(ctor, "stop", keyCatcherStop);
	Nan::SetPrototypeMethod(ctor, "setCallback", keyCatcherSetCallback);
	Nan::SetPrototypeMethod(ctor, "update", keyCatcherUpdate);

	target->Set(Nan::New("KeyCatcher").ToLocalChecked(), ctor->GetFunction());
}

NAN_METHOD(KeyCatcherWrapper::keyCatcherNew) {
	if (!info.IsConstructCall())
		return Nan::ThrowError(Nan::New("use new keyword").ToLocalChecked());

	auto* keyCatcherWrapper = new KeyCatcherWrapper(); // todo smart pointer?
	keyCatcherWrapper->keyCatcher = new KeyCatcher();
	keyCatcherWrapper->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(KeyCatcherWrapper::keyCatcherBegin) {
	auto* keyCatcherWrapper = Nan::ObjectWrap::Unwrap<KeyCatcherWrapper>(info.This());
	KeyCatcher* keyCatcher = keyCatcherWrapper->keyCatcher;
	keyCatcher->begin();
}

NAN_METHOD(KeyCatcherWrapper::keyCatcherStop) {
	auto* keyCatcherWrapper = Nan::ObjectWrap::Unwrap<KeyCatcherWrapper>(info.This());
	KeyCatcher* keyCatcher = keyCatcherWrapper->keyCatcher;
	keyCatcher->stop();
}

NAN_METHOD(KeyCatcherWrapper::keyCatcherSetCallback) {
	auto* keyCatcherWrapper = Nan::ObjectWrap::Unwrap<KeyCatcherWrapper>(info.This());
	keyCatcherWrapper->callback.Reset(info[0].As<v8::Function>());

	auto callback = [keyCatcherWrapper](bool down, int code, bool injected) {
		v8::Local<v8::Value> args[] {Nan::New(down), Nan::New(code), Nan::New(injected)};
		return Nan::Call(keyCatcherWrapper->callback, 3, args).ToLocalChecked()->BooleanValue();
	};

	KeyCatcher* keyCatcher = keyCatcherWrapper->keyCatcher;
	keyCatcher->setCallback(callback);
}

NAN_METHOD(KeyCatcherWrapper::keyCatcherUpdate) {
	auto* keyCatcherWrapper = Nan::ObjectWrap::Unwrap<KeyCatcherWrapper>(info.This());
	KeyCatcher* keyCatcher = keyCatcherWrapper->keyCatcher;
	keyCatcher->update();
}
