#include "StdAfx.h"
#include "Test_LogicSystem.h"

#include "../LogicSystem/Logic.h"
#include "../LogicSystem/CompositeExpression.h"
#include "../LogicSystem/SingleExpression.h"

#include "../MindElement/ConceptInteractTable.h"
#include "../MindElement/Concept.h"

#include "../MindInterface/iCerebrum.h"

#include "../DataCollection/GrammaPattern.h"

using namespace DataCollection;
using namespace Mind;
using namespace LogicSystem;


Test_LogicSystem::Test_LogicSystem(void)
{
}


Test_LogicSystem::~Test_LogicSystem(void)
{
}

void Test_LogicSystem::RunTest()
{
	iCerebrum* brain=iCerebrum::Instance();

	Test_Expression();
	Test_Logic_Determine();
}

void Test_LogicSystem::Test_Expression()
{
	iCerebrum* brain=iCerebrum::Instance();
	vector<PartOfSpeech> pos;
	pos.push_back(Numeral);
	pos.push_back(Adjective);
	pos.push_back(Preposition);
	pos.push_back(Numeral);
	GrammarPattern pattern(pos);
	for (int i=0;i<200;++i)
	{
		brain->IncreasePatternFreqency(pos);
	}


	shared_ptr<SingleExpression> expre(new SingleExpression("������һ��"));
	shared_ptr<iConceptInteractTable> table=expre->GetInteractTable();
	vector<pair<shared_ptr<iConcept>,shared_ptr<iConcept>>> relations=table->GetAllRelations();
}

void Test_LogicSystem::Test_Logic_Determine()
{
	shared_ptr<CompositeExpression> condition(new CompositeExpression());
	condition->AddExpression("������һ��");
	condition->AddExpression("�����ڶ���");

	shared_ptr<Expression> conclusion_true(new SingleExpression("������һ"));
	shared_ptr<Expression> conclusion_false(new SingleExpression("һ������"));

	Check(Logic::Determine(condition,conclusion_true)==True);
	Check(Logic::Determine(condition,conclusion_true)==False);
}


