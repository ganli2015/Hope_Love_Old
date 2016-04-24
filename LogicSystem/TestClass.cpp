#include "StdAfx.h"
#include "TestClass.h"
#include "Logic.h"
#include "CompositeExpression.h"
#include "SingleExpression.h"

#include "../MindElement/ConceptInteractTable.h"
#include "../MindElement/Concept.h"

#include "../Mind/Cerebrum.h"

#include "../DataCollection/GrammaPattern.h"

using namespace DataCollection;
using namespace Mind;

namespace LogicSystem
{
	TestClass::TestClass(void)
	{
	}


	TestClass::~TestClass(void)
	{
	}

	void TestClass::RunTest()
	{
		Cerebrum* brain=Cerebrum::Instance();

		Test_Expression();
		Test_Logic_Determine();
	}

	void TestClass::Test_Expression()
	{
		Cerebrum* brain=Cerebrum::Instance();
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


		shared_ptr<SingleExpression> expre(new SingleExpression("二大于一。"));
		shared_ptr<ConceptInteractTable> table=expre->GetInteractTable();
		vector<pair<shared_ptr<Concept>,shared_ptr<Concept>>> relations=table->GetAllRelations();
	}

	void TestClass::Test_Logic_Determine()
	{
		shared_ptr<CompositeExpression> condition(new CompositeExpression());
		condition->AddExpression("二大于一。");
		condition->AddExpression("三大于二。");

		shared_ptr<Expression> conclusion_true(new SingleExpression("三大于一"));
		shared_ptr<Expression> conclusion_false(new SingleExpression("一大于三"));

		Check(Logic::Determine(condition,conclusion_true)==True);
		Check(Logic::Determine(condition,conclusion_true)==False);
	}

}

