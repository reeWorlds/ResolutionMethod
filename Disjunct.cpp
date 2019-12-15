#include "Disjunct.h"

Disjunct::Disjunct()
{
	for (int i = 0; i < ALPHABETSIZE; i++)
	{
		data1[i] = data0[i] = 0;
	}
}

int Disjunct::haveContraPair()
{
	for (int i = 0; i < ALPHABETSIZE; i++)
	{
		if (data1[i] == 1 && data0[i] == 1)
		{
			return 1;
		}
	}

	return 0;
}

int Disjunct::isEmpty()
{
	for (int i = 0; i < ALPHABETSIZE; i++)
	{
		if (data1[i] == 1 || data0[i] == 1)
		{
			return 0;
		}
	}

	return 1;
}

std::string Disjunct::toString()
{
	if (isEmpty())
	{
		return "Empty";
	}

	std::string result;

	for (int i = 0; i < ALPHABETSIZE; i++)
	{
		if (data1[i] == 1)
		{
			result += char('A' + i);
			result += "v";
		}

		if (data0[i] == 1)
		{
			result += "!";
			result += char('A' + i);
			result += "v";
		}
	}

	result.pop_back();

	return result;
}