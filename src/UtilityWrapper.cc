#include "UtilityWrapper.h"

Nan::Persistent<v8::ObjectTemplate> UtilityWrapper::constructor;

NAN_MODULE_INIT(UtilityWrapper::Init) {
	v8::Local<v8::ObjectTemplate> ctor = Nan::New<v8::ObjectTemplate>();
	constructor.Reset(ctor);

	Nan::SetMethod(ctor, "getClipboardText", utilityGetClipboardText);
	Nan::SetMethod(ctor, "setClipboardText", utilitySetClipboardText);
	Nan::SetMethod(ctor, "clearClipboardText", utilityClearClipboardText);
	Nan::SetMethod(ctor, "sendKeys", utilitySendKeys);
	Nan::SetMethod(ctor, "screenSize", utilityScreenSize);
	Nan::SetMethod(ctor, "mousePosition", utilityMousePosition);
	Nan::SetMethod(ctor, "foregroundTitle", utilityForegroundTitle);
	Nan::SetAccessor(ctor, Nan::New("SendKeysState").ToLocalChecked(), utilitySendKeyStates);

	target->Set(Nan::New("Utility").ToLocalChecked(), ctor->NewInstance());
}

NAN_METHOD(UtilityWrapper::utilityGetClipboardText) {
	std::string clipboardText = Utility::getClipboardText();
	info.GetReturnValue().Set(Nan::New(clipboardText).ToLocalChecked());
}

NAN_METHOD(UtilityWrapper::utilitySetClipboardText) {
	Utility::setClipboardText(*Nan::Utf8String(info[0]));
}

NAN_METHOD(UtilityWrapper::utilityClearClipboardText) {
	Utility::clearClipboardText();
}

NAN_METHOD(UtilityWrapper::utilitySendKeys) {
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

NAN_METHOD(UtilityWrapper::utilityScreenSize) {
	std::pair<LONG, LONG> mouse = Utility::screenSize();
	v8::Local<v8::Array> outputs = Nan::New<v8::Array>(2);
	outputs->Set(0, Nan::New<v8::Number>(mouse.first));
	outputs->Set(1, Nan::New<v8::Number>(mouse.second));
	info.GetReturnValue().Set(outputs);
}

NAN_METHOD(UtilityWrapper::utilityMousePosition) {
	POINT mouse = Utility::mousePosition();
	v8::Local<v8::Array> outputs = Nan::New<v8::Array>(2);
	outputs->Set(0, Nan::New<v8::Number>(mouse.x));
	outputs->Set(1, Nan::New<v8::Number>(mouse.y));
	info.GetReturnValue().Set(outputs);
}

NAN_METHOD(UtilityWrapper::utilityForegroundTitle) {
	std::string title = Utility::foregroundTitle();
	info.GetReturnValue().Set(Nan::New(title).ToLocalChecked());
}

NAN_GETTER(UtilityWrapper::utilitySendKeyStates) {
	v8::Local<v8::Object> SendKeyStatesObj = Nan::New<v8::Object>();
	Nan::Set(SendKeyStatesObj, Nan::New("UP").ToLocalChecked(), Nan::New(Utility::UP));
	Nan::Set(SendKeyStatesObj, Nan::New("DOWN").ToLocalChecked(), Nan::New(Utility::DOWN));
	Nan::Set(SendKeyStatesObj, Nan::New("TYPE").ToLocalChecked(), Nan::New(Utility::TYPE));
	info.GetReturnValue().Set(SendKeyStatesObj);
}
