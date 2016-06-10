#include "StdAfx.h"
#include "ConfigureManager.h"

#include "../Mind/Cerebrum.h"

#include "../MindElement/MindElementCreator.h"

#include "../LogicSystem/LogicElementCreator.h"
#include "../LogicSystem/LogicKnowledge.h"

#include "../CommonTools/ConfigureInfoManager.h"

namespace ManageWrapper
{
	ConfigureManager::ConfigureManager(void)
	{
	}

	void ConfigureManager::Configure()
	{
		shared_ptr<CommonTool::ConfigureInfoManager> cfgInfo=CommonTool::ConfigureInfoManager::GetInstance();
		cfgInfo->UpdateConfigure();

		shared_ptr<Mind::MindElementCreator> mindElementCreator(new Mind::MindElementCreator());
		Mind::iMindElementCreator::SetImp(mindElementCreator);

		shared_ptr<LogicSystem::LogicElementCreator> logicElementCreator(new LogicSystem::LogicElementCreator());
		LogicSystem::iLogicElementCreator::SetImp(logicElementCreator);

		Mind::Cerebrum *brain=Mind::Cerebrum::Instance();
		brain->SetLogicKnowledge(new LogicSystem::LogicKnowledge());
		Mind::iCerebrum::SetInstance(brain);
	}
}


