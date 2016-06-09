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

			param.from=Identity("��",0);
			param.to=Identity("��",0);

			vector<pair<string,string>> expect;
			expect.push_back(make_pair("��","�̶�"));
			expect.push_back(make_pair("�̶�","�ø�"));
			expect.push_back(make_pair("�ø�","�Է�"));
			expect.push_back(make_pair("��","�ø�"));

			param.expect=expect;

			res.push_back(param);
		}

		{
			Param_DeepInteraction param;

			param.from=Identity("��",0);
			param.to=Identity("��",0);

			vector<pair<string,string>> expect;
			expect.push_back(make_pair("��","����"));
			expect.push_back(make_pair("��","����"));

			param.expect=expect;
			res.push_back(param);
		}

		{
			Param_DeepInteraction param;

			param.from=Identity("��",0);
			param.to=Identity("��",0);

			vector<pair<string,string>> expect;
			expect.push_back(make_pair("����","��"));
			expect.push_back(make_pair("����","��"));
			expect.push_back(make_pair("��","����"));

			param.expect=expect;
			res.push_back(param);
		}

		return res;
	}

}
