#include <iostream>
#include <fmt/core.h>

#include "clients/hostClient.h"
#include "messages/messageCollection.h"
#include "messages/errorMessage.h"
#include "console.h"

#include <type_traits>

int main() {
	MessageCollection collection;

	Console console(&collection);
	HostClient client(&collection);

	for(;;) {
		console.handleInput();

		if(collection.hasChanged()) console.redrawMessageArea();

		Sleep(100);
	}
}
