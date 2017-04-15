#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <time.h>

#ifndef BUNNIES_H
#define BUNNIES_H

struct Bunny;
extern Bunny* begin;
char colours[];
extern const int startBunnies;
extern int currentMutants;

void newBunny(char col);
void killBunny(Bunny* del);
void printInfo(const Bunny* num);
void printList();
void progress();
void agingProcess();
void reproduction();
void infectBunnies();
void printColonyInformation();
void changeBunnyInformation();
void saveColony();
void saveBunny(const Bunny* num);
void changeAge(Bunny* a);
void changeGender(Bunny* a);
void changeColour(Bunny* a);
void changeName(Bunny* a);
void changeMutant(Bunny *a);
int  countBunnies();
int  countBunniesByGender(char gen);
int  countMutants();
bool checkForDeath(Bunny* a);
bool checkForExtinction();
bool checkForProperMale();
bool checkForProperFemale(Bunny* check);
std::string resolveColour(char i);
#endif