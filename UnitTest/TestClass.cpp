#include "StdAfx.h"
#include "TestClass.h"
#include "../Mind/Cerebrum.h"

#include "Test_SentenceAnalysisAlgorithm.h"
#include "Test_NeuralNetworkDesign.h"
#include "Test_Mind.h"
#include "Test_Mathmatic.h"
#include "Test_LogicSystem.h"
#include "Test_ReactionAnalysisAlgorithm.h"

#define  Register(class_name) \
	_tests.push_back(shared_ptr<Test>(new MyTest<Test_##class_name>()));

TestClass::TestClass(void)
{
	Register(SentenceAnalysisAlgorithm);
	Register(NeuralNetworkDesign);
	Register(Mind);
 	Register(Mathmatic);
	Register(LogicSystem);
	Register(ReactionAnalysisAlgorithm);
}


TestClass::~TestClass(void)
{
}

void TestClass::RunTest()
{
	Mind::iCerebrum::SetInstance(Mind::Cerebrum::Instance());

	for (unsigned int i=0;i<_tests.size();++i)
	{
		_tests[i]->Run();
	}
}