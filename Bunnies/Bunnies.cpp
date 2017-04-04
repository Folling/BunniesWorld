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

int iterationCount = 0;

Bunny* newBunny(char col) {
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
		return begin;
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
		return begin;
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
	agingProcess();
	Bunny* check = begin;
	while (check->next != 0) {
		Bunny* temp = check;
		check = check->next;
		if (check == 0) break;
		if (checkForDeath(temp)) killBunny(temp);		
	}
	if(checkForDeath(check)) killBunny(check);
	infectBunnies();
	reproduction();
	iterationCount++;
}

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

//counts how many females/male bunnies there are
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

bool checkForProperMale() {
	Bunny* check = begin;
	if (check->age >= 2 && check->gender == 'm')return true;
	while (check->next != 0) {
		check = check->next;
		if (check->age >= 2 && check->gender == 'm') return true;
	}
	return false;
}

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
	std::cout << "Total Bunnies:	      " << countBunnies() << std::endl;
	std::cout << "Males:                " << countBunniesByGender('m') << std::endl;
	std::cout << "Females:              " << countBunniesByGender('f') << std::endl;
	std::cout << "Amount of mutants:    " << countMutants() << std::endl;
	std::cout << "Amount of iterations: " << iterationCount << std::endl;
	std::cout << "\n\n";
}

std::string resolveColour(char i) {
	switch (i) {
		case 'w' : return "white";
		case 'b' : return "black";
		case 's' : return "spotted";
		case 'r' : return "brown";
		default  : return "undefined colour";
	}
}