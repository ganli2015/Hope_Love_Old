#include "StdAfx.h"
#include "ConfigureManager.h"

#include "../Mind/Cerebrum.h"

#include "../MindElement/MindElementCreator.h"

#include "../LogicSystem/LogicElementCreator.h"

namespace ManageWrapper
{
	ConfigureManager::ConfigureManager(void)
	{
	}

	void ConfigureManager::Configure()
	{
		shared_ptr<Mind::MindElementCreator> mindElementCreator(new Mind::MindElementCreator());
		Mind::iMindElementCreator::SetImp(mindElementCreator);

		shared_ptr<LogicSystem::LogicElementCreator> logicElementCreator(new LogicSystem::LogicElementCreator());
		LogicSystem::iLogicElementCreator::SetImp(logicElementCreator);

		Mind::iCerebrum::SetInstance(Mind::Cerebrum::Instance());
	}
}


