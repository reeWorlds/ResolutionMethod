#include "Disjunction.h"

Disjunction::Disjunction()
{
	type = FORMULA::disjunction;
}

Disjunction::~Disjunction()
{
	for (auto& it : children)
	{
		//delete it;
	}
}