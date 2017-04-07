#include "Bunnies.h"
#include "Menu.h"
#include <conio.h>

int main() {
	Menu mainscreen;
	srand((unsigned int)time(0));
	for (int i = 0; i < startBunnies; i++) {
		newBunny(colours[rand() % 4]);
	}
	currentMutants = countMutants();
	mainscreen.display();
	while (true) {
		mainscreen.getChoice();
		if (checkForExtinction()) break;
	}
	std::cout << "It seems all Bunnies have died!\n";
	_getch();
}