#include "StdAfx.h"
#include "Command.h"
#include "../DataWrapperCPP/DataWrapper.h"

#include "../CommonTools/ConfigureInfoManager.h"

using namespace CommonTool;

Command::Command(void)
{
	UpdateConfigureManager();
}


Command::~Command(void)
{
}

void Command::UpdateConfigureManager() const
{
	shared_ptr<ConfigureInfoManager> cfgManager=ConfigureInfoManager::GetInstance();
	cfgManager->UpdateConfigure();

}

