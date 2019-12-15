#pragma once

enum FORMULA
{
	variable,
	negation,
	conjunction,
	disjunction
};

class Formula
{
public:

	FORMULA type;
};