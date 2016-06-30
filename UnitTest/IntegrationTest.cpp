#include "stdafx.h"
#include "IntegrationTest.h"

#include "../Mind/Cerebrum.h"

#include "../MindElement/MindElementCreator.h"

#include "../LogicSystem/LogicElementCreator.h"
#include "../LogicSystem/LogicKnowledge.h"
#include "../LogicSystem/LogicKnowledgeInitializer.h"

#include "../CommonTools/ConfigureInfoManager.h"

#include "../DataWrapperCPP/DataWrapper.h"

#include "../CommandList/SpeakCommand.h"

#define ADD_PARAM(in, out) \
{	\
ParamIntegration param;	\
param.input = in;	\
param.output.push_back(out);	\
res.push_back(param);	\
}	

#define ADD_PARAM2(in, out1,out2) \
{	\
ParamIntegration param;	\
param.input = in;	\
param.output.push_back(out1);	\
param.output.push_back(out2);	\
res.push_back(param);	\
}

IntegrationTest::IntegrationTest() 
{
}


IntegrationTest::~IntegrationTest()
{
}

std::vector<ParamIntegration> IntegrationTest::GenerateSamples()
{
	Initialize();

	vector<ParamIntegration> res;

	ADD_PARAM2("莫莫我爱你", "我也爱你", "人家也爱你")
	
	ADD_PARAM("三加二等于多少", "五")

	ADD_PARAM("六加上四等于几", "十")

	ADD_PARAM("零加三等于几", "三")

	ADD_PARAM("二乘二等于几", "四")

	return res;
}

void IntegrationTest::Initialize()
{
	///ConfigureInfoManager
	shared_ptr<CommonTool::ConfigureInfoManager> cfgInfo = CommonTool::ConfigureInfoManager::GetInstance();
	cfgInfo->UpdateConfigure();

	///MindElementCreator
	shared_ptr<Mind::MindElementCreator> mindElementCreator(new Mind::MindElementCreator());
	Mind::iMindElementCreator::SetImp(mindElementCreator);

	///LogicElementCreator
	shared_ptr<LogicSystem::LogicElementCreator> logicElementCreator(new LogicSystem::LogicElementCreator());
	LogicSystem::iLogicElementCreator::SetImp(logicElementCreator);

	///iCerebrum
	Mind::Cerebrum *brain = Mind::Cerebrum::Instance();
	Mind::iCerebrum::SetInstance(brain);

	///iLogicKnowledge
	LogicSystem::LogicKnowledge* knowledge = new LogicSystem::LogicKnowledge();
	LogicSystem::LogicKnowledgeInitializer knowledgeInit;
	knowledgeInit.Initialize("HopeLoveData\\LogicStatements.txt", knowledge);
	brain->SetLogicKnowledge(knowledge);
}

bool IntegrationTest::StringInVector(const string str, const vector<string>& strVec)
{
	for (unsigned int i=0;i<strVec.size();++i)
	{
		if (str == strVec[i])
		{
			return true;
		}
	}

	return false;
}

#ifdef _RUN_INTEGRATION_TEST

INSTANTIATE_TEST_CASE_P(Integration, IntegrationTest, testing::ValuesIn(IntegrationTest::GenerateSamples()));

TEST_P(IntegrationTest, InputAndOutputSentence)
{
	ParamIntegration param = GetParam();

	DataWrapperCPP::DataWrapper_Sentence* data = new DataWrapperCPP::DataWrapper_Sentence();
	data->AddInputSentence(param.input);

	SpeakCommand* command = new SpeakCommand(data);
	command->Update();

	string result=data->GetNewOutSentence();

	ASSERT_TRUE(IntegrationTest::StringInVector(result, param.output))
		<< "Result: " + result + "\n"
		+ "Expect: " + param.output.front() + "\n";

	delete command;
	delete data;
}

#endif // _RUN_INTEGRATION_TEST
