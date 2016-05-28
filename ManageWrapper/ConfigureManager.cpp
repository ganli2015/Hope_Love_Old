#include "StdAfx.h"
#include "ConfigureManager.h"

#include "../Mind/Cerebrum.h"

#include "../MindElement/MindElementCreator.h"

namespace ManageWrapper
{
	ConfigureManager::ConfigureManager(void)
	{
	}

	void ConfigureManager::Configure()
	{
		shared_ptr<Mind::MindElementCreator> mindElementCreator(new Mind::MindElementCreator());
		Mind::iMindElementCreator::SetImp(mindElementCreator);

		Mind::iCerebrum::SetInstance(Mind::Cerebrum::Instance());
	}
}


