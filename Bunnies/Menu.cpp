#include "Menu.h"
#include "Bunnies.h"
#include <iostream>
#include <fstream>

//generic method to display the options each user has, probably am going to just make this visible by command
void Menu::display() {
	std::cout << "Please select what you want to do: \n";
	std::cout << "1 -- print the list\n";
	std::cout << "2 -- have another iteration of the colony\n";
	std::cout << "3 -- save the current colony\n";
	std::cout << "4 -- exit the programm\n";
}

//gets user input
void Menu::getChoice() {
	int choice;
	std::cin >> choice;
		switch (choice)
		{
		case 1: printList();
			break;
		case 2: progress();
			break;
		case 3: saveColony();
			break;
		case 4: exit(1);
			break;
	}
}

//method to save the colony, to be inmplemented.
void Menu::saveColony() {

}