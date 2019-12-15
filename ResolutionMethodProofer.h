#pragma once

#include <QString>

#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include "Disjunct.h"

class ResolutionMethodProofer
{
	static int contraPairCount(Disjunct& a, Disjunct& b);
	static Disjunct getResolvente(Disjunct& a, Disjunct& b);

	static void setUsed(int pos, std::vector<std::pair<int, int> >& parent, std::vector<int>& used);

public:

	static std::vector<QString> tryToProof(std::vector<Disjunct> data);

};