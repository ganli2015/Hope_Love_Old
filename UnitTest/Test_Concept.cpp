#include "StdAfx.h"
#include "Test_Concept.h"

#include "FuncForTest.h"

#include "../Mind/Cerebrum.h"

#include "../MindElement/Concept.h"

#include "../MindInterface/iCerebrum.h"
#include "../MindInterface/iConceptInteractTable.h"


namespace Mind
{
	INSTANTIATE_TEST_CASE_P(Test_Mind, Test_Concept, testing::ValuesIn(Test_Concept::GenerateSamples()));

	TEST_P(Test_Concept,DeepInteraction)
	{
		MEMOCHECK;

		Cerebrum* brain=Cerebrum::Instance();
		iCerebrum::SetInstance(brain);

		Param_DeepInteraction param=GetParam();

		shared_ptr<iConcept> from=brain->GetConcept(param.from);
		shared_ptr<iConcept> to=brain->GetConcept(param.to);

		shared_ptr<iConceptInteractTable> table=from->DeepInteractWith(to);
		table->RemoveDuplicated();

		ASSERT_TRUE(FuncForTest::PairSameWithTable(param.expect,table))
			<<"expect: \n"+FuncForTest::TablePairToString(param.expect)
			+"result: \n"+table->GetString();

		iCerebrum::KillInstance();
	}

	vector<Param_DeepInteraction> Test_Concept::GenerateSamples()
	{
		vector<Param_DeepInteraction> res;

		{
			Param_DeepInteraction param;

			param.from=Identity("爱",0);
			param.to=Identity("你",0);

			vector<pair<string,string>> expect;
			expect.push_back(make_pair("大","程度"));
			expect.push_back(make_pair("程度","好感"));
			expect.push_back(make_pair("好感","对方"));
			expect.push_back(make_pair("大","好感"));

			param.expect=expect;

			res.push_back(param);
		}

		{
			Param_DeepInteraction param;

			param.from=Identity("不",0);
			param.to=Identity("老",0);

			vector<pair<string,string>> expect;
			expect.push_back(make_pair("否定","年龄"));
			expect.push_back(make_pair("大","年龄"));

			param.expect=expect;
			res.push_back(param);
		}

		{
			Param_DeepInteraction param;

			param.from=Identity("三",0);
			param.to=Identity("大",0);

			vector<pair<string,string>> expect;
			expect.push_back(make_pair("整数","大"));
			expect.push_back(make_pair("整数","加"));
			expect.push_back(make_pair("加","整数"));

			param.expect=expect;
			res.push_back(param);
		}

		return res;
	}

}
