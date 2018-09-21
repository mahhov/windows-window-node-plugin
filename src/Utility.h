#ifndef WINDOWSPLUGIN_UTILITY_H
#define WINDOWSPLUGIN_UTILITY_H

#include <string>
#include <vector>
#include <windows.h>

class Utility {
  public:
	static std::string getClipboardText();

	static void sendKeys(std::vector<std::vector<WORD>> vkss);

	static POINT mousePosition();

  private:
	static INPUT makeKeyInput(WORD vk, bool up = false);
};

#endif //WINDOWSPLUGIN_UTILITY_H
