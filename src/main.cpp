#include <iostream>
#include <fmt/core.h>

#include "messages/messageCollection.h"
#include "console.h"
#include "messages/errorMessage.h"

#include <type_traits>

int main() {
	MessageCollection collection;

	Console console(&collection);

	for(;;) {
		console.handleInput();

		Sleep(100);
	}
}
