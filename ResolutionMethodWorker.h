#pragma once

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include <QtCore>
#include <QString>
#include <QLabel>
#include <QFont>
#include "ui_ResolutionMethodWorker.h"

#include <string>
#include <vector>

#include "Disjunct.h"
#include "Parser.h"
#include "FormulaTransformator.h"
#include "ResolutionMethodProofer.h"

class ResolutionMethodWorker : public QMainWindow
{
	Q_OBJECT

public:
	ResolutionMethodWorker(QWidget *parent = Q_NULLPTR);

private:
	Ui::ResolutionMethodWorkerClass ui;

	std::vector<QLabel*> proofLabels;

public slots:

	void startResolutionMethod();
};

/*

ex1: PvQ,!PvR,!QvS,!RvSvP,!SvP|=P
ex2: Pv!Q,!QvSv!P,!S,Q,RvS|=
ex3: PvQ,QvSv!P,!Q|=

1) A->B,C->D,AvC|=BvD
2) AvB,B->C,!Av!C|=!AvD
3) B->A,C->D,B&!D|=A&!C
4) A->C,B->D,AvB|=D&C
5) A->B,C->D,!BvD&C|=!Av!C
6) !A->B,Q->D,!Bv!D|=Av!Q
7) A->C,!D->B,!A->!B|=!C->D
8) AvBvC,!AvC,!B|=!C
9) AvB->C->D,!A&!B|=C&!D
10)A->B,C->D,!Bv!D|=!Av!C
11)A->B,C->D|=AvC->BvD
12)A->B,C->D|=A&C->BvD
13)A->B,C->D|=AvC->B&D
14)A->B,C->D|=A&C->B&D

add) A->B,C->D,E->F|=(AvCvE)->(BvDvF)

*/