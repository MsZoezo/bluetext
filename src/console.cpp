//
// Created by Zoezo on 1/15/2023.
//

#include "console.h"
#include "messages/systemMessage.h"
#include "messages/userMessage.h"
#include "messages/errorMessage.h"

Console::Console(MessageCollection* messageCollection) {
	this->messageCollection = messageCollection;

	this->in = GetStdHandle(STD_INPUT_HANDLE);
	this->out = GetStdHandle(STD_OUTPUT_HANDLE);

	if (this->in == INVALID_HANDLE_VALUE || this->out == INVALID_HANDLE_VALUE) {
		fmt::print(fg(fmt::color::red), "FATAL - Failed to get handle for input or output. Error -> {}", GetLastError());
		exit(1);
	}

	if(GetConsoleMode(this->in, &this->oldMode) == 0) {
		fmt::print(fg(fmt::color::red), "FATAL - Failed to get console mode. Error -> {}", GetLastError());
		exit(1);
	}

	DWORD mode = ENABLE_WINDOW_INPUT;

	if(SetConsoleMode(this->in, mode) == 0) {
		fmt::print(fg(fmt::color::red), "FATAL - Failed to set console mode. Error -> {}", GetLastError());
		exit(1);
	}

	CONSOLE_SCREEN_BUFFER_INFO info;
	if(GetConsoleScreenBufferInfo(this->out, &info) == 0) {
		fmt::print(fg(fmt::color::red), "FATAL - Failed to get console screen buffer info. Error -> {}", GetLastError());
		exit(1);
	}

	this->size = info.dwSize;

	this->messageCollection->push(new SystemMessage("Welcome to bluetext! Enjoy your stay \3"));

	this->redraw();
}

Console::~Console() {
	if(SetConsoleMode(this->in, this->oldMode) == 0) {
		fmt::print(fg(fmt::color::red), "FATAL - Failed to reset console mode. Error -> {}", GetLastError());
		exit(1);
	}
}

void Console::handleInput() {
	DWORD numberOfEvents = 0;

	// This is an error but it may be non trivial? should keep track of how many fail in a row...
	if(GetNumberOfConsoleInputEvents(this->in, &numberOfEvents) == 0) return;

	if(numberOfEvents == 0) return;

	INPUT_RECORD buffer[128];
	DWORD read, i;

	std::optional<WINDOW_BUFFER_SIZE_RECORD> resizeEvent = std::nullopt;

	bool handledKeyEvent = false;
	bool handledResizeEvent = false;

	ReadConsoleInput(in, buffer, 128, &read);

	for(i = 0; i < read; i++) {
		switch(buffer[i].EventType) {
			case KEY_EVENT:
				this->onKeyEvent(buffer[i].Event.KeyEvent);
				handledKeyEvent = true;
				break;

			case WINDOW_BUFFER_SIZE_EVENT:
				resizeEvent = buffer[i].Event.WindowBufferSizeEvent;
				handledResizeEvent = true;
				break;
		}
	}

	if(resizeEvent.has_value()) this->onResizeEvent(resizeEvent.value());

	if(handledResizeEvent) redraw();
	else if(handledKeyEvent) redrawInputArea();
}

void Console::onKeyEvent(KEY_EVENT_RECORD event) {
	if(event.wVirtualKeyCode == 81 && event.dwControlKeyState & LEFT_CTRL_PRESSED) exit(0);

	if(!event.bKeyDown) return;

	if(event.wVirtualKeyCode == 8) {
		this->inputBuffer.pop();
		return;
	}

	if(event.wVirtualKeyCode == 13) {
		if(this->inputBuffer.length() == 0) {
			this->messageCollection->push(new ErrorMessage("Can't send empty message."));
			this->redrawMessageArea();
			return;
		}

		std::string message = this->inputBuffer.retrieve(100);
		this->messageCollection->push(new UserMessage(message, "TestUser"));
		this->redrawMessageArea();

		this->inputBuffer.clear();
		return;
	}

	if(event.uChar.AsciiChar != '\0') {
		this->inputBuffer.add(event.uChar.AsciiChar);
	}
}

void Console::onResizeEvent(WINDOW_BUFFER_SIZE_RECORD event) {
	this->size = event.dwSize;
}

void Console::redraw() {
	fmt::print("\x1b[2J");

	fmt::print("\x1b[1;1H");
	fmt::print("\x1b[107m{}\x1b[0m", std::string(this->size.X, ' '));

	std::string title = "BlueText";

	fmt::print("\x1b[1;{}H", (this->size.X - title.length()) / 2);
	fmt::print(" {} ", title);

	fmt::print("\x1b[{};1H", this->size.Y - 1);
	fmt::print("{}", std::string(this->size.X, 223));

	if(this->inputBuffer.length() != 0) this->redrawInputArea();
	if(this->messageCollection->size() != 0) this->redrawMessageArea();
}

void Console::redrawInputArea() {
	fmt::print("\x1b[{};1H", this->size.Y);
	fmt::print("{}", std::string(this->size.X, ' '));

	fmt::print("\x1b[{};1H", this->size.Y);
	fmt::print(this->inputBuffer.retrieve(this->size.X));
}

void Console::redrawMessageArea() {
	// calculate capacity of remaining space.
	int capacity = this->size.X * (this->size.Y - 3);

	fmt::print("\x1b[2;1H");
	fmt::print(fmt::format("{}", std::string(capacity, ' ')));

	int index = this->messageCollection->size() - 1;

	std::string printable;

	// idk how correct this is but it works for now?
	while(capacity > 0 && index != -1) {
		Message* message = this->messageCollection->at(index);

		int length = message->getLength();
		std::string text = message->getText();

		int lines = ceil((double) length / (double) this->size.X);
		int totalSize = lines * this->size.X;

		capacity -= totalSize;

		if(totalSize > length) text.append("\n");

		printable.insert(0, text);

		index -= 1;
	}

	fmt::print("\x1b[2;1H");
	fmt::print(printable);
}
