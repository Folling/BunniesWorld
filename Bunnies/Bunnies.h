#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>

#ifndef BUNNIES_H
#define BUNNIES_H

struct Bunny;
char colours[];

Bunny* newBunny(char col);
void killBunny(Bunny* del);
void printInfo(const Bunny* num);
void printList();
void progress();
void agingProcess();
void reproduction();
void infectBunnies();
void printColonyInformation();
int  countBunnies();
int  countBunniesByGender(char gen);
int  countMutants();
bool checkForDeath(Bunny* a);
bool checkForExtinction();
bool checkForProperMale();
bool checkForProperFemale(Bunny* check);
std::string resolveColour(char i);
#endif