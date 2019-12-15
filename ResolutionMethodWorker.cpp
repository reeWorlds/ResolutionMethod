#include "ResolutionMethodWorker.h"

ResolutionMethodWorker::ResolutionMethodWorker(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(startResolutionMethod()));
}

void ResolutionMethodWorker::startResolutionMethod()
{
	std::string input = ui.lineEdit->text().toStdString();

	if (input == "")
	{
		return;
	}

	if (!(Parser::isCorrectFormula(input)))
	{
		QMessageBox::warning(this, "Error!", "Incorrect input!");

		return;
	}

	std::vector<Formula*> formulas = Parser::parseInput(input);

	std::vector<Disjunct> disjunctions;

	for (auto& it: formulas)
	{
		std::vector<Disjunct> temp = FormulaTransformator::simplifyFormula(it);

		for (auto& itt : temp)
		{
			disjunctions.push_back(itt);
		}
	}
	
	std::vector<QString> proof = ResolutionMethodProofer::tryToProof(disjunctions);

	if (proof.empty())
	{
		QMessageBox::warning(this, "Result", "No empty disjunnct!");

		return;
	}
	else
	{
		for (auto& it : proofLabels)
		{
			delete it;
		}
		proofLabels.clear();
		

		for (int i = 0; i < int(proof.size()); i++)
		{
			QLabel* label = new QLabel;

			QFont font;
			font.setFamily("Arial");
			font.setPointSize(24);

			proofLabels.push_back(label);
			label->setText(proof[i]);
			label->setFont(font);

			ui.verticalLayout_2->addWidget(label, i);
		}

		return;
	}
}