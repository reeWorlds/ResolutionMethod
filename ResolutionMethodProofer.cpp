#include "ResolutionMethodProofer.h"

int ResolutionMethodProofer::contraPairCount(Disjunct& a, Disjunct& b)
{
	int count = 0, i;

	for (i = 0; i < ALPHABETSIZE; i++)
	{
		if ((a.data1[i] == 1 && b.data0[i] == 1) || (a.data0[i] == 1 && b.data1[i] == 1))
		{
			count++;
		}
	}

	return count;
}

Disjunct ResolutionMethodProofer::getResolvente(Disjunct& a, Disjunct& b)
{
	Disjunct result;
	int i;

	for (i = 0; i < ALPHABETSIZE; i++)
	{
		result.data0[i] = std::max(a.data0[i], b.data0[i]);
		result.data1[i] = std::max(a.data1[i], b.data1[i]);

		if (result.data0[i] == 1 && result.data1[i] == 1)
		{
			result.data0[i] = 0;
			result.data1[i] = 0;
		}
	}

	return result;
}

void ResolutionMethodProofer::setUsed(int pos, std::vector<std::pair<int, int> >& parent, std::vector<int>& used)
{
	if (pos < 0)
	{
		return;
	}

	if (used[pos] == 1)
	{
		return;
	}

	used[pos] = 1;
	setUsed(parent[pos].first, parent, used);
	setUsed(parent[pos].second, parent, used);
}

std::vector<QString> ResolutionMethodProofer::tryToProof(std::vector<Disjunct> data)
{
	std::set<std::string> usedStrings;

	std::vector<std::pair<int, int> > parent;
	std::vector<int> used;
	std::vector<Disjunct> info;

	for (auto& it : data)
	{
		info.push_back(it);
		parent.push_back({ -1, -1 });
		used.push_back(1);

		usedStrings.insert(info.back().toString());
	}

	int i, j, last;

	for (i = 0; i < info.size(); i++)
	{
		last = info.size();

		for (j = i + 1; j < last; j++)
		{
			if (contraPairCount(info[i], info[j]) == 1)
			{
				Disjunct resolventa = getResolvente(info[i], info[j]);

				if (usedStrings.find(resolventa.toString()) != usedStrings.end())
				{
					continue;
				}

				info.push_back(resolventa);
				parent.push_back({ i, j });
				used.push_back(0);

				usedStrings.insert(resolventa.toString());

				if (info.back().isEmpty())
				{
					setUsed(int(info.size()) - 1, parent, used);

					std::vector <QString> result;
					QString tempString;
					int formulaCount = 1;

					for (int l = 0; l<int(info.size()); l++)
					{
						if (used[l] == 1)
						{
							tempString = QString::number(formulaCount) + ")" + QString::fromStdString(info[l].toString());

							if (l < data.size())
							{
								tempString += "{input}";
							}
							else
							{
								tempString += "{" + QString::number(used[parent[l].first]) + "," + QString::number(used[parent[l].second]) + "}";
							}

							result.push_back(tempString);

							used[l] = formulaCount;
							formulaCount++;
						}
					}

					return result;
				}
			}
		}
	}

	return std::vector<QString>();
}