#pragma once
#include <iostream>
#include <string>
#include <cstdlib>

#ifndef BUNNIES_H
#define BUNNIES_H

struct Bunny;

Bunny* newBunny();
void killBunny(int num);
void printInfo(const Bunny* num);
void printList();
void progress();
bool checkForFemale();
bool checkForDeath(Bunny* a);
bool checkForExtinction();
#endif