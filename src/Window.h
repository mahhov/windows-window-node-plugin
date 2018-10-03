#ifndef WINDOW_H
#define WINDOW_H

#include <windows.h>
#include <string>
#include <vector>
#include <functional>

class Window {
  public:
	explicit Window(std::string name);

	void makeWindow();

	void destroyWindow();

	void setSystemTrayCallback(std::function<void()> callback);

	void beginClipboardListener();

	void endClipboardListener();

	void setClipboardCallback(std::function<void(std::string)> callback);

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
	std::function<void()> systemTrayCallback;
	std::function<void(std::string)> clipboardCallback;
	int width, lineHeight;
	std::vector<std::string> lines;
};

#endif
