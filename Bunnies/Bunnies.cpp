#include "Bunnies.h"

struct Bunny
{
	int age;
	std::string gender;
	std::string colour;
	std::string name;
	bool mutant;
	Bunny* next;
};

std::string maleNames[] = { "John", "Peter", "Nathan", "Lars", "Jack", "Danny" };
std::string femaleNames[] = { "Lessy", "Jessica", "Lilly", "Lucy", "Mary", "Sophie" };
std::string colours[] = { "white", "black", "spotted", "brown" };

Bunny* begin = 0;


Bunny* newBunny() {
	//when list is empty the first bunny becomes it head
	if (begin == 0) {
		Bunny* node = new Bunny;
		node->age = 0;
		node->gender = rand() % 2 == 0 ? "male" : "female";
		//if male the bunny gets a male name if female a female one
		node->name = node->gender == "male" ?  maleNames[rand() % 6] : femaleNames[rand() % 6];
		//every 50th bunny on average will be a mutant
		node->mutant = rand() % 50 == 0 ? true : false;
		node->colour = colours[rand() % 4];
		node->next = 0;
		begin = node;
		return begin;
	}
	//otherwise it will be added to the end of the list, thus the list is alphabetically sorted
	else {
		Bunny* node = begin;
		Bunny* newBunny;
		while (node->next != 0)	node = node->next;
		newBunny = new Bunny;
		newBunny->age = 0;
		newBunny->gender = rand() % 2 == 0 ? "male" : "female";
		//if male the bunny gets a maleName if female a female one
		newBunny->name = node->gender == "male" ? maleNames[rand() % 6] : femaleNames[rand() % 6];
		//every 50th bunny on average will be a mutant
		newBunny->mutant = rand() % 50 == 0 ? true : false;
		newBunny->colour = colours[rand() % 4];
		newBunny->next = 0;
		node->next = newBunny;
		return begin;
	}
}

//prints the info for the numths bunny in the list
void printInfo(const Bunny* num) {
	std::cout << "Gender    ----    " << num->gender << std::endl;
	std::cout << "Name      ----    " << num->name << std::endl;
	std::cout << "Age       ----    " << num->age << std::endl;
	std::cout << "Colour    ----    " << num->colour << std::endl;
}

//prints every bunny's information in the list
void printList() {
	Bunny* Bunny = begin;
	if (begin == 0) {
		std::cout << "All Bunnies are dead!\n";
	}
	else {
		int counter = 2;
		std::cout << "1. Bunny: \n";
		printInfo(begin);
		while (Bunny->next != 0) {
			Bunny = Bunny->next;
			std::cout << counter << ". Bunny: \n";
			printInfo(Bunny); 
			counter++;
		}
	}
}

//if a bunny dies this method will kill it
void killBunny(Bunny* del) {
	//if the Bunny to kill is the first bunny
	if (del == begin) {	
		begin = begin->next;
		delete del;
	}
	//if the bunny to kill is any other bunny
	else {
		Bunny* temp = del->next;
		del->next = temp->next;
		delete temp;
	}
}

void progress(){
	Bunny* cursor = begin;
	//if the head-bunny of the list is to be killed
	while (cursor != 0) {
		cursor->age += 1;
		if (checkForDeath(cursor)) {
			killBunny(cursor);	
		}
		else break;
	}
	//if any other of the bunnies is to be killed
	while (cursor->next != 0) {
		cursor->next->age += 1;
		if (checkForDeath(cursor->next)) killBunny(cursor);
		cursor = cursor->next;
	}
}

//returns true should there be a female above the age of 2, probably have to overwrite this as children are supposed to have the same colour as their mother
bool checkForFemale() {
	Bunny* check = begin;
	if (check->gender == "female" && check->age >= 2) return true;
	while (check->next != 0) {
		check = check->next;
		if (check->age >= 2 && check->gender == "female") return true;
	}
	return false;
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
}