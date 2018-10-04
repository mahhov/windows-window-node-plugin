#ifndef WINDOWSPLUGIN_WINDOWWRAPPER_H
#define WINDOWSPLUGIN_WINDOWWRAPPER_H

#include <nan.h>
#include "Window.h"

class WindowWrapper : public Nan::ObjectWrap {
  public:
	static NAN_MODULE_INIT(Init);

	static NAN_METHOD(windowNew);

	static NAN_METHOD(windowMakeWindow);

	static NAN_METHOD(windowDestroyWindow);

	static NAN_METHOD(windowSetSystemTrayCallback);

	static NAN_METHOD(windowSetClipboardCallback);

	static NAN_METHOD(windowSetFocusCallback);

	static NAN_METHOD(windowSetKeyCallback);

	static NAN_METHOD(windowUpdate);

	static NAN_METHOD(windowSetGeometry);

	static NAN_METHOD(windowSetLines);

	static NAN_METHOD(windowShow);

	static NAN_METHOD(windowHide);

	static NAN_METHOD(windowSetLine);

	static NAN_GETTER(windowVisible);

	static NAN_GETTER(windowHasWindow);

  private:
	Window* window;
	Nan::Callback systemTrayCallback;
	Nan::Callback clipboardCallback;
	Nan::Callback focusCallback;
	Nan::Callback keyCallback;
	static Nan::Persistent<v8::FunctionTemplate> constructor;
};

#endif