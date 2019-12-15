#pragma once

#include "formula.h"

class Negation : public Formula
{
public:

	Formula* child;

	Negation();
	~Negation();
};