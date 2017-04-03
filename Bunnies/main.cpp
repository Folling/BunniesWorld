#include "Bunnies.h"
#include "Menu.h"
#include <ctime>
#include <conio.h>

int main() {
	Menu mainscreen;
	srand((unsigned int)time(0));
	for (int i = 0; i < 5; i++) {
		newBunny();
	}
	while (true) {		
		mainscreen.display();
		mainscreen.getChoice();
		//if (checkForExtinction()) break;
	}
	std::cout << "It seems all Bunnies have died!\n";
	_getch();
}