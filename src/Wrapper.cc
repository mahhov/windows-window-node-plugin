#include <nan.h>
#include <windows.h>
#include "UtilityWrapper.h"
#include "WindowWrapper.h"
#include "KeyCatcherWrapper.h"
#include "Utility.h"
#include "Window.h"
#include "KeyCatcher.h"

NAN_MODULE_INIT(InitModule) {
	UtilityWrapper::Init(target);
	WindowWrapper::Init(target);
	KeyCatcherWrapper::Init(target);
}

NODE_MODULE(myModule, InitModule);
