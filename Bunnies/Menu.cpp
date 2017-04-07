#include "Menu.h"
#include <iostream>

//generic method to display the options each user has, probably am going to just make this visible by command
void Menu::display() {
	std::cout << "Please select what you want to do: \n";
	std::cout << "1 -- print the list\n";
	std::cout << "2 -- have another iteration of the colony\n";
	std::cout << "3 -- provide general informations about the colony\n";
	std::cout << "4 -- change the characteristics of a Bunny\n";
	std::cout << "5 -- save the current colony\n";
	std::cout << "6 -- exit the programm\n";
	std::cout << "7 -- show this menu again\n";
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
		case 3: printColonyInformation();
			break;
		case 4: changeBunnyInformation();
			break;
		case 5: saveColony();
			break;
		case 6: exit(1);
			break;
		case 7: display();
			break;
		default: std::cout << "Invalid command!\n\n";
	}
}