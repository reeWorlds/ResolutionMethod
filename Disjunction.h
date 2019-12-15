#pragma once

#include <vector>
#include "Formula.h"

class Disjunction : public Formula
{
public:

	std::vector<Formula*> children;

	Disjunction();
	~Disjunction();
};