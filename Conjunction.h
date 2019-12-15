#pragma once

#include <vector>
#include "Formula.h"

class Conjunction : public Formula
{
public:

	std::vector<Formula*> children;

	Conjunction();
	~Conjunction();
};