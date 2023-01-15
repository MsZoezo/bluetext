//
// Created by Zoezo on 1/15/2023.
//

#ifndef BLUETEXT_CONSOLE_H
#define BLUETEXT_CONSOLE_H

#include <windows.h>
#include <optional>
#include <fmt/core.h>
#include <fmt/color.h>

#include "messages/messageCollection.h"
#include "inputBuffer.h"

class Console {
private:
	MessageCollection* messageCollection;
	InputBuffer inputBuffer;

	HANDLE in, out;
	DWORD oldMode;
	COORD size;

	void onKeyEvent(KEY_EVENT_RECORD event);
	void onResizeEvent(WINDOW_BUFFER_SIZE_RECORD event);

public:
	Console(MessageCollection* messageCollection);
	~Console();

	void handleInput();

	void redraw();
	void redrawInputArea();
	void redrawMessageArea();
};


#endif //BLUETEXT_CONSOLE_H
