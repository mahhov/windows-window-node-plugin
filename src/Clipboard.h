#ifndef WINDOWSPLUGIN_CLIPBOARD_H
#define WINDOWSPLUGIN_CLIPBOARD_H

#include <string>
#include <windows.h>

class Clipboard {
  public:
	static std::string getClipboardText();

	static void sendCtrlC();

  private:
	static INPUT makeKeyInput(WORD vk, DWORD flags = 0);
};

#endif //WINDOWSPLUGIN_CLIPBOARD_H
