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
		condition->AddExpression("������һ��");
		condition->AddExpression("�����ڶ���");

		shared_ptr<Expression> conclusion_true(new Expression("������һ"));
		shared_ptr<Expression> conclusion_false(new Expression("һ������"));

		Check(Logic::Determine(condition,conclusion_true)==True);
		Check(Logic::Determine(condition,conclusion_true)==False);
	}

}

