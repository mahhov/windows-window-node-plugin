#ifndef WINDOWSPLUGIN_UTILITY_H
#define WINDOWSPLUGIN_UTILITY_H

#include <string>
#include <vector>
#include <windows.h>

class Utility {
  public:
	static std::string getClipboardText();

	static void setClipboardText(std::string text);

	static void clearClipboardText();

	static void sendKeys(std::vector<std::vector<WORD>> vkss);

	static std::pair<LONG, LONG> screenSize();

	static POINT mousePosition();

	static std::string foregroundTitle();

  private:
	static INPUT makeKeyInput(WORD vk, bool up = false);
};

#endif //WINDOWSPLUGIN_UTILITY_H
