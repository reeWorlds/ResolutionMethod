#pragma once

#include <string>
#include <vector>
#include "Formula.h"
#include "Variable.h"
#include "Negation.h"
#include "Conjunction.h"
#include "Disjunction.h"
#include "Disjunct.h"

class FormulaTransformator
{
	static Formula* pushNegation(Formula* formula);
	static Formula* transformFormula(Formula* formula);

	static void disToConRecursion(std::vector<Formula*>& data, int pos, Disjunction* tempResult, std::vector<Formula*>& result);
	static std::vector<Formula*> disjunctionToConjunction(Disjunction* formula);

	static void conToDisRecursion(std::vector<Formula*>& data, int pos, Conjunction* tempResult, std::vector<Formula*>& result);
	static std::vector<Formula*> conjunctionToDisjunction(Conjunction* formula);

	static Disjunct formulaToDisjunct(Formula* formula);

	static Conjunction* copyConjunction(Conjunction* formula);
	static Disjunction* copyDisjunction(Disjunction* formula);

public:

	static std::vector<Disjunct> simplifyFormula(Formula* root);


};