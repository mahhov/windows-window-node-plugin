#ifndef WINDOWSPLUGIN_KEYCATCHER_H
#define WINDOWSPLUGIN_KEYCATCHER_H

#include <windows.h>
#include <Windows.h>
#include <functional>

class KeyCatcher {
  public:
	void begin();

	void stop();

	void setCallback(std::function<bool(bool down, int code)> callback);

	void update();

  private:
	static LRESULT CALLBACK process(int code, WPARAM wParam, LPARAM lParam);

	HHOOK hhook;
	static KeyCatcher* callbackThis;
	std::function<bool(bool down, int code)> callback;
};


#endif
