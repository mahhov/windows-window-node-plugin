#ifndef WINDOWSPLUGIN_KEYCATCHERWRAPPER_H
#define WINDOWSPLUGIN_KEYCATCHERWRAPPER_H

#include <nan.h>
#include "KeyCatcher.h"

class KeyCatcherWrapper : public Nan::ObjectWrap {
  public:
	static NAN_MODULE_INIT(Init);

	static NAN_METHOD(keyCatcherNew);

	static NAN_METHOD(keyCatcherBegin);

	static NAN_METHOD(keyCatcherStop);

	static NAN_METHOD(keyCatcherSetCallback);

	static NAN_METHOD(keyCatcherUpdate);

  private:
	KeyCatcher* keyCatcher;
	Nan::Callback callback;
	static Nan::Persistent<v8::FunctionTemplate> constructor;
};

#endif