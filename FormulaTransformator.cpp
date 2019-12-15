#include "FormulaTransformator.h"

Formula* FormulaTransformator::pushNegation(Formula* formula)
{
	if (formula->type == FORMULA::variable)
	{
		Variable* temp = new Variable;
		temp->name = ((Variable*)formula)->name;

		return temp;
	}
	else if (formula->type == FORMULA::conjunction)
	{
		Conjunction* temp = new Conjunction;

		for (auto& it : ((Conjunction*)formula)->children)
		{
			temp->children.push_back(pushNegation(it));
		}

		return temp;
	}
	else if (formula->type == FORMULA::disjunction)
	{
		Disjunction* temp = new Disjunction;

		for (auto& it : ((Disjunction*)formula)->children)
		{
			temp->children.push_back(pushNegation(it));
		}

		return temp;
	}
	else if (formula->type == FORMULA::negation)
	{
		Negation* info = (Negation*)formula;

		if (info->child->type == FORMULA::variable)
		{
			return info;
		}
		else if (info->child->type == FORMULA::negation)
		{
			return pushNegation(((Negation*)(info->child))->child);
		}
		else if (info->child->type == FORMULA::conjunction)
		{
			Disjunction* temp = new Disjunction();
			for (auto& it : ((Conjunction*)(info->child))->children)
			{
				Negation* tempNegation = new Negation;
				tempNegation->child = it;

				temp->children.push_back(pushNegation(tempNegation));
			}

			return temp;
		}
		else if (info->child->type == FORMULA::disjunction)
		{
			Conjunction* temp = new Conjunction();
			for (auto& it : ((Disjunction*)(info->child))->children)
			{
				Negation* tempNegation = new Negation;
				tempNegation->child = it;

				temp->children.push_back(pushNegation(tempNegation));
			}

			return temp;
		}
	}
}

Conjunction* FormulaTransformator::copyConjunction(Conjunction* formula)
{
	Conjunction* newFormula = new Conjunction;

	for (auto& it : formula->children)
	{
		newFormula->children.push_back(it);
	}

	return newFormula;
}

Disjunction* FormulaTransformator::copyDisjunction(Disjunction* formula)
{
	Disjunction* newFormula = new Disjunction;

	for (auto& it : formula->children)
	{
		newFormula->children.push_back(it);
	}

	return newFormula;
}

void FormulaTransformator::disToConRecursion(std::vector<Formula*>& data, int pos, Disjunction* tempResult, std::vector<Formula*>& result)
{
	if (pos == data.size())
	{
		result.push_back(copyDisjunction(tempResult));
		
		return;
	}

	if (data[pos]->type == FORMULA::variable || data[pos]->type == FORMULA::negation)
	{
		tempResult->children.push_back(data[pos]);
		disToConRecursion(data, pos + 1, tempResult, result);
		tempResult->children.pop_back();

		return;
	}
	else if(data[pos]->type == FORMULA::conjunction) // i am sure it is conjunction anyway (!) [i hope]
	{
		for (auto& it : (((Conjunction*)(data[pos]))->children))
		{
			tempResult->children.push_back(it);
			disToConRecursion(data, pos + 1, tempResult, result);
			tempResult->children.pop_back();
		}

		return;
	}
}

std::vector<Formula*> FormulaTransformator::disjunctionToConjunction(Disjunction* formula)
{
	std::vector<Formula*> result;
	Disjunction* tempResult = new Disjunction;

	disToConRecursion(formula->children, 0, tempResult, result);

	return result;
}

void FormulaTransformator::conToDisRecursion(std::vector<Formula*>& data, int pos, Conjunction* tempResult, std::vector<Formula*>& result)
{
	if (pos == data.size())
	{
		result.push_back(copyConjunction(tempResult));

		return;
	}

	if (data[pos]->type == FORMULA::variable || data[pos]->type == FORMULA::negation)
	{
		tempResult->children.push_back(data[pos]);
		conToDisRecursion(data, pos + 1, tempResult, result);
		tempResult->children.pop_back();

		return;
	}
	else if (data[pos]->type == FORMULA::disjunction) // i am sure it is disjunction anyway (!) [i hope]
	{
		for (auto& it : (((Disjunction*)(data[pos]))->children))
		{
			tempResult->children.push_back(it);
			conToDisRecursion(data, pos + 1, tempResult, result);
			tempResult->children.pop_back();
		}

		return;
	}
}

std::vector<Formula*> FormulaTransformator::conjunctionToDisjunction(Conjunction* formula)
{
	std::vector<Formula*> result;
	Conjunction* tempResult = new Conjunction;

	conToDisRecursion(formula->children, 0, tempResult, result);

	return result;
}

Formula* FormulaTransformator::transformFormula(Formula* formula)
{
	// reduce deep of conjunctions and disjunctions
	// be sure to push negation before

	if (formula->type == FORMULA::variable)
	{
		return formula;
	}
	else if (formula->type == FORMULA::negation)
	{
		return formula;
	}
	else if (formula->type == FORMULA::conjunction)
	{
		Conjunction* result = new Conjunction;

		for (auto& it : ((Conjunction*)formula)->children)
		{
			Formula* transformedFormula = transformFormula(it);

			if (transformedFormula->type == FORMULA::variable || transformedFormula->type == FORMULA::negation)
			{
				result->children.push_back(transformedFormula);
			}
			else if (transformedFormula->type == FORMULA::conjunction)
			{
				for (auto& itt : ((Conjunction*)transformedFormula)->children)
				{
					result->children.push_back(itt);
				}
			}
			else if (transformedFormula->type == FORMULA::disjunction)
			{
				std::vector<Formula*> conjunctions = disjunctionToConjunction((Disjunction*)transformedFormula);

				for (auto& itt : conjunctions)
				{
					result->children.push_back(itt);
				}
			}
		}

		return result;
	}
	else if (formula->type == FORMULA::disjunction)
	{
		Disjunction* result = new Disjunction;

		for (auto& it : ((Disjunction*)formula)->children)
		{
			Formula* transformedFormula = transformFormula(it);

			if (transformedFormula->type == FORMULA::variable || transformedFormula->type == FORMULA::negation)
			{
				result->children.push_back(transformedFormula);
			}
			else if (transformedFormula->type == FORMULA::disjunction)
			{
				for (auto& itt : ((Disjunction*)transformedFormula)->children)
				{
					result->children.push_back(itt);
				}
			}
			else if (transformedFormula->type == FORMULA::conjunction)
			{
				std::vector<Formula*> disjunctions = conjunctionToDisjunction((Conjunction*)transformedFormula);

				for (auto& itt : disjunctions)
				{
					result->children.push_back(itt);
				}
			}
		}

		return result;
	}
}

Disjunct FormulaTransformator::formulaToDisjunct(Formula* formula)
{
	// I hope there is not any conjunction there

	Disjunct result;

	if (formula->type == FORMULA::variable)
	{
		result.data1[((Variable*)formula)->name - 'A'] = 1;
	}
	else if (formula->type == FORMULA::negation)
	{
		result.data0[((Variable*)(((Negation*)formula)->child))->name - 'A'] = 1;
	}
	else if (formula->type == FORMULA::disjunction)
	{
		for (auto& it : ((Disjunction*)formula)->children)
		{
			if (it->type == FORMULA::variable)
			{
				result.data1[((Variable*)it)->name - 'A'] = 1;
			}
			else if (it->type == FORMULA::negation)
			{
				result.data0[((Variable*)(((Negation*)it)->child))->name - 'A'] = 1;
			}
		}
	}

	return result;
}

std::vector<Disjunct> FormulaTransformator::simplifyFormula(Formula* root)
{
	Formula* root1 = pushNegation(root);

	if (root1->type == FORMULA::variable)
	{
		std::vector<Disjunct> result;
		result.push_back(Disjunct());
		result[0].data1[((Variable*)root1)->name - 'A'] = 1;

		return result;
	}
	else if (root1->type == FORMULA::negation)
	{
		std::vector<Disjunct> result;
		result.push_back(Disjunct());
		result[0].data0[((Variable*)(((Negation*)root1)->child))->name - 'A'] = 1;

		return result;
	}
	else
	{
		Formula* root2 = transformFormula(root1);

		if (root2->type == FORMULA::disjunction)
		{
			std::vector<Formula*> root3 = disjunctionToConjunction((Disjunction*)root2);

			std::vector<Disjunct> result;
			Disjunct tempDisjunct;

			for (auto& it : root3)
			{
				tempDisjunct = formulaToDisjunct(it);

				if (!tempDisjunct.haveContraPair())
				{
					result.push_back(tempDisjunct);
				}
			}

			return result;
		}
		else
		{
			std::vector<Disjunct> result;
			Disjunct tempDisjunct;

			for (auto& it : ((Conjunction*)root2)->children)
			{
				tempDisjunct = formulaToDisjunct(it);

				if (!tempDisjunct.haveContraPair())
				{
					result.push_back(tempDisjunct);
				}
			}

			return result;
		}
	}
}
