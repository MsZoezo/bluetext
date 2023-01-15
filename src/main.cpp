#include <iostream>
#include <fmt/core.h>

#include "clients/client.h"
#include "messages/messageCollection.h"
#include "messages/errorMessage.h"
#include "console.h"

#include <type_traits>

int main() {
	MessageCollection collection;

	Console console(&collection);
	Client client(&collection);

	for(;;) {
		console.handleInput();

		Sleep(100);
	}
}
