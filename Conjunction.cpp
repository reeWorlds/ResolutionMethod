#include "Conjunction.h"

Conjunction::Conjunction()
{
	type = FORMULA::conjunction;
}

Conjunction::~Conjunction()
{
	for (auto& it : children)
	{
		//delete it;
	}
}