#ifndef WINDOW_H
#define WINDOW_H

#include <windows.h>
#include <string>
#include <vector>

class Window {
  public:
	void makeWindow();

	void update();

	void setGeometry(int x, int y, int width, int height);

	void setLines(int lineCount, int lineHeight);

	void show();

	void hide();

	void setLine(int index, std::string line);

  private:
	void draw(HWND hwnd);

	static LRESULT CALLBACK
	process(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	HWND hwnd;
	int width, lineHeight;
	std::vector<std::string> lines;
};

#endif
