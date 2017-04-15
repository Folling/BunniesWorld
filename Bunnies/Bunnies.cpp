#include "Bunnies.h"
#include "Menu.h"

struct Bunny
{
	int age;
	char gender;
	char colour;
	std::string name;
	bool mutant;
	Bunny* next;
};

std::string maleNames[] = { "John", "Peter", "Nathan", "Lars", "Jack", "Danny" };
std::string femaleNames[] = { "Lessy", "Jessica", "Lilly", "Lucy", "Mary", "Sophie" };
char colours[] = { 'w', 'b', 's', 'r' };

//head of the list
Bunny* begin = 0;

const int startBunnies = 5;
int iterationCount = 0;
int currentBunnies = startBunnies;
int currentMutants;
int diedBunnies = 0;

void newBunny(char col) {
	//when list is empty the first bunny becomes it head
	if (begin == 0) {
		Bunny* node = new Bunny;
		node->age = 0;
		node->gender = rand() % 2 == 0 ? 'm' : 'f';
		//if male the bunny gets a male name if female a female one
		node->name = (node->gender == 'm')?  maleNames[rand() % 6] : femaleNames[rand() % 6];
		//every 50th bunny on average will be a mutant
		node->mutant = rand() % 50 == 0 ? true : false;
		//colour will be set randomly if it's just one of the first 5 bunnies, otherwise the colour will be given by the mother
		node->colour = col;
		node->next = 0;
		begin = node;
		//return begin;
	}
	//otherwise it will be added to the end of the list, thus the list is sorted by age
	else {
		Bunny* node = begin;
		Bunny* newBunny;
		while (node->next != 0)	node = node->next;
		newBunny = new Bunny;
		newBunny->age = 0;
		newBunny->gender = rand() % 2 == 0 ? 'm' : 'f';
		//if male the bunny gets a maleName if female a female one
		newBunny->name = (node->gender == 'm')? maleNames[rand() % 6] : femaleNames[rand() % 6];
		//every 50th bunny on average will be a mutant
		newBunny->mutant = (rand() % 50 == 0 ? true : false);
		//colour will be set randomly if it's just one of the first 5 bunnies, otherwise the colour will be given by the mother
		newBunny->colour = col;
		newBunny->next = 0;
		node->next = newBunny;
		//return begin;
	}
}

//prints information for the given bunny;
void printInfo(const Bunny* num) {
	std::cout << "Gender    ----    " << ((num->gender == 'm') ? "male" : "female") << "\n";;
	std::cout << "Name      ----    " << num->name << std::endl;
	std::cout << "Age       ----    " << num->age << std::endl;
	std::cout << "Colour    ----    " << resolveColour(num->colour) << std::endl;
	std::cout << "This bunny is ";
	if (num->mutant == false) std::cout << "not ";
	std::cout << "a Mutant!" << std::endl;
}

//prints every bunny's information in the list
void printList() {
	Bunny* check = begin;
	if (begin == 0) {
		std::cout << "All Bunnies are dead!\n";
	}
	else {
		int counter = 2;
		std::cout << "1. Bunny: \n";
		printInfo(begin);
		while (check->next != 0) {
			check = check->next;
			std::cout << counter << ". Bunny: \n";
			printInfo(check);
			counter++;
		}
	}
}

//if a bunny should die this method will kill it
void killBunny(Bunny* del) {
	Bunny* check = begin;
	if (check == del) {
		begin = begin->next;
		delete del;
		return;
	}
	while(check->next != del) {
		check = check->next;
	}
	check->next = del->next;
	delete del;
}

//calculates another iteration of the bunny colony, bunnies die, give birth become mutants etc.
void progress() {
	diedBunnies = 0;
	agingProcess();
	Bunny* check = begin;
	while (check->next != 0) {
		Bunny* temp = check;
		check = check->next;
		if (checkForDeath(temp)) {
			killBunny(temp);
			diedBunnies++;
		}
	}
	if (checkForDeath(check)) {
		killBunny(check);
		diedBunnies++; //why do only so few bunnies die?
	}
	infectBunnies();
	reproduction();
	iterationCount++;
	currentBunnies = countBunnies();
	currentMutants = countMutants();
}

//calculates how many newborn bunnies there will be
void reproduction() {
	if (!checkForProperMale()) return;
	Bunny* check = begin;
	if (checkForProperFemale(check)) newBunny(check->colour);
	while (check->next != 0) {
		check = check->next;
		if (checkForProperFemale(check)) newBunny(check->colour);
	}
}

//increases the age of each bunny by one after each turn
void agingProcess() {
	Bunny* check = begin;
	check->age += 1;
	while (check->next != 0) {
		check->next->age += 1;
		check = check->next;
	}
}

//counts how many females/male bunnies there are in the colony
int countBunniesByGender(char gen) {
	Bunny* check = begin;
	int count = 0;
	if (check->gender == gen) count++;
	while (check->next != 0) {
		check = check->next;
		if (check->gender == gen) count++;		
	}
	return count;
}

//counts how many bunnies there are in the colony
int countBunnies() {
	int count = 0;
	Bunny* check = begin;
	if (check != 0)count++;
	while (check->next != 0) {
		count++;
		check = check->next;
	}
	return count;
}

//counts how many mutants there are
int countMutants() {
	Bunny* check = begin;
	int count = 0;
	if (check->mutant) count++;
	while (check->next != 0) {
		check = check->next;
		if (check->mutant) count++;
	}
	return count;
}

//checks whether there is atleast one male above or = the age of 2 in the colony
bool checkForProperMale() {
	Bunny* check = begin;
	if (check->age >= 2 && check->gender == 'm')return true;
	while (check->next != 0) {
		check = check->next;
		if (check->age >= 2 && check->gender == 'm') return true;
	}
	return false;
}

//infects as many bunnies each turn as there are mutants
void infectBunnies() {
	Bunny* check = begin;
	for (int i = 0; i < countMutants(); i++) {
		while (check->next != 0) {
			if (check->mutant == true) check = check->next;
			else {
				if (rand() % 4 == 0) {
					check->mutant = true;
					break;
				}
				else check = check->next;
			}
		}
	}
}

//returns true if the given bunny is female and older or = 2 years
bool checkForProperFemale(Bunny* check){
	if (check->age >= 2 && check->gender == 'f')return true;
	else return false;
}

//checks whether a bunny is too old and thus dies
bool checkForDeath(Bunny* a) {
	if (a->mutant == true && a->age >= 50) return true;
	if (a->mutant == false && a->age >= 10) return true;
	return false;
}

//checks whether all bunnies are dead
bool checkForExtinction() {
	if (begin == 0) return true;
	else return false;
}

//provides general information about the colony
void printColonyInformation() {
	std::cout << "Total Bunnies:	          " << currentBunnies << std::endl;
	std::cout << "Males:                    " << countBunniesByGender('m') << std::endl;
	std::cout << "Females:                  " << countBunniesByGender('f') << std::endl;
	std::cout << "Amount of mutants:        " << currentMutants << std::endl;
	std::cout << "Amount of iterations:     " << iterationCount << std::endl;
	std::cout << "Deaths in last iteration: " << diedBunnies << std::endl;
	std::cout << "\n\n";
}

//takes a char as an input and returns the corresponding string
std::string resolveColour(char i) {
	switch (i) {
		case 'w' : return "white";
		case 'b' : return "black";
		case 's' : return "spotted";
		case 'r' : return "brown";
		default  : return "undefined colour";
	}
}

//gives the user the option to change informations about bunnies, aka Name, age, etc
void changeBunnyInformation() {
	using namespace std;
	int choice, age = 0;
	std::string newName = " ";
	char newGen = ' ';
	char newCol = ' ';
	Bunny* check = ::begin;
	cout << "Please Enter which Bunny you want to edit: \t" << endl;
	if (cin >> choice) {
		if (choice > currentBunnies) {
			cout << "That Bunny doesn't exist!\n";
			changeBunnyInformation();
		}
		for (int i = 1; i < choice; i++) {
			check = check->next;
		}
		cout << "What attribute do you want to change?\n 1-5 for age, gender, colour, name, mutant";
		if (cin >> choice) {
			switch (choice) {
			case 1: changeAge(check);
				break;
			case 2: changeGender(check);
				break;
			case 3: changeColour(check);
				break;
			case 4: changeName(check);
				break;
			case 5: changeMutant(check);
				break;
			default: cout << "Invalid input!\n";
				break;				
			}

		}
	}
}

//function to change the age of a bunny
void changeAge(Bunny* a) {
	int choice;
	std::cout << "Please enter the new age: \t";
	if (std::cin >> choice) {
		if ((a->mutant == true && choice < 50) || (a->mutant == false && choice < 10)) a->age = choice;
		else {
			std::cout << "Sorry the age you entered is invalid for the specific bunny!\n";
			changeAge(a);
		}
	}
	else {
		std::cout << "Invalid input!\n";
		changeAge(a);
	}
}

//function to change the gender of a bunny
void changeGender(Bunny* a) {
	if (a->gender == 'w') a->gender = 'm';
	else a->gender = 'w';
}

//function to change the colour of a bunny
void changeColour(Bunny* a) {
	char choice;
	std::cout << "Please enter the new colour: \t";
	std::cin >> choice;
	if (choice == 'w' || choice == 'b' || choice == 'r' || choice == 's') {
		if (a->colour != choice) a->colour = choice;
		else {
			std::cout << "Sorry the bunny is already of the colour you entered!\n";
			changeColour(a);
		}
	}
	else {
		std::cout << "Invalid input!\n";
		changeColour(a);
	}
}

//function to change the name of a bunny
void changeName(Bunny* a) {
	std::string choice;
	std::cout << "Please enter the new name: \t";
	if (std::cin >> choice) {
		if (!isupper(choice[0])) {
			std::cout << "Please capitilize the name!\n";
			changeName(a);
		}
		else if(a->name != choice) a->name = choice;
		else {
			std::cout << "Sorry the bunny already has the name you entered!\n";
			changeName(a);
		}	
	}
	else {
		std::cout << "Invalid input!\n";
		changeName(a);
	}
}

//function to switch whether a bunny is mutant or not
void changeMutant(Bunny *a) {
	if (a->mutant == true) a->mutant = false;
	else a->mutant = true;
}

//saves all bunnies and their data to a text file
void saveColony() {
	using namespace std;
	std::ofstream myfile;
	myfile.open("BunniesList.txt");
	Bunny* check = ::begin;
	int counter = 2;
	myfile << "1. Bunny: \n\n";
	//saveBunny(begin);
	myfile << "Gender    ----    " << ((::begin->gender == 'm') ? "male" : "female") << "\n";;
	myfile << "Name      ----    " << ::begin->name << std::endl;
	myfile << "Age       ----    " << ::begin->age << std::endl;
	myfile << "Colour    ----    " << resolveColour(::begin->colour) << endl;
	myfile << "This bunny is ";
	if (::begin->mutant == false) myfile << "not ";
	myfile << "a Mutant!" << endl << endl;

	while (check->next != 0) {
		check = check->next;
		myfile << counter << ". Bunny: \n";
		myfile << "Gender    ----    " << ((check->gender == 'm') ? "male" : "female") << "\n";;
		myfile << "Name      ----    " << check->name << std::endl;
		myfile << "Age       ----    " << check->age << std::endl;
		myfile << "Colour    ----    " << resolveColour(check->colour) << endl;
		myfile << "This bunny is ";
		if (check->mutant == false) myfile  << "not ";
		myfile << "a Mutant!" << endl << endl;
		counter++;
	}
}