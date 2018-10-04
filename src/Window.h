#ifndef WINDOW_H
#define WINDOW_H

#include <windows.h>
#include <string>
#include <vector>
#include <functional>

class Window {
  public:
	explicit Window(std::string name);

	void makeWindow(bool focusable);

	void destroyWindow();

	void setSystemTrayCallback(std::function<void()> callback);

	void setClipboardCallback(std::function<void(std::string)> callback);

	void setFocusCallback(std::function<void(bool focus)> callback);

	void setKeyCallback(std::function<void(int key)> callback);

	void update();

	void setGeometry(int x, int y, int width, int height);

	void setLines(int lineCount, int lineHeight);

	void show();

	void hide();

	void setLine(int index, std::string line);

	bool visible {};
	bool hasWindow {};

  private:
	void addSystemTrayIcon();

	void markDrawDirty();

	void draw();

	static LRESULT CALLBACK process(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	HWND hwnd;
	std::string name;
	bool focusable;
	std::function<void()> systemTrayCallback;
	std::function<void(std::string)> clipboardCallback;
	std::function<void(bool)> focusCallback;
	std::function<void(int)> keyCallback;
	int width, lineHeight;
	std::vector<std::string> lines;
};

#endif
