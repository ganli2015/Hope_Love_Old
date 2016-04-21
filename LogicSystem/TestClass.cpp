#include "StdAfx.h"
#include "TestClass.h"
#include "Logic.h"
#include "CompositeExpression.h"

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
		shared_ptr<CompositeExpression> condition(new CompositeExpression());
		condition->AddExpression("二大于一。");
		condition->AddExpression("三大于二。");

		shared_ptr<Expression> conclusion_true(new Expression("三大于一"));
		shared_ptr<Expression> conclusion_false(new Expression("一大于三"));

		Check(Logic::Determine(condition,conclusion_true)==True);
		Check(Logic::Determine(condition,conclusion_true)==False);
	}

}

