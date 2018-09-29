#ifndef WINDOWSPLUGIN_UTILITYWRAPPER_H
#define WINDOWSPLUGIN_UTILITYWRAPPER_H

#include <nan.h>
#include "Utility.h"

class UtilityWrapper : public Nan::ObjectWrap {
  public:
	static NAN_MODULE_INIT(Init);

	static NAN_METHOD(utilityGetClipboardText);

	static NAN_METHOD(utilitySetClipboardText);

	static NAN_METHOD(utilityClearClipboardText);

	static NAN_METHOD(utilitySendKeys);

	static NAN_METHOD(utilityScreenSize);

	static NAN_METHOD(utilityMousePosition);

	static NAN_METHOD(utilityForegroundTitle);

  private:
	static Nan::Persistent<v8::ObjectTemplate> constructor;
};

#endif