#include "Bunnies.h"
#include "Menu.h"
#include <conio.h>

int main() {
	Menu mainscreen;
	srand((unsigned int)time(0));
	for (int i = 0; i < 15000; i++) {
		newBunny(colours[rand() % 4]);
	}
	mainscreen.display();
	while (true) {
		mainscreen.getChoice();
		if (checkForExtinction()) break;
	}
	std::cout << "It seems all Bunnies have died!\n";
	_getch();
}