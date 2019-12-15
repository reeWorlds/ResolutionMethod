#pragma once

#include <string>
#include <vector>

#define ALPHABETSIZE 26

class Disjunct
{
public:

	Disjunct();

	int data1[26]; // simple variable
	int data0[26]; // variable with negation

	int haveContraPair();
	int isEmpty();

	std::string toString();
};