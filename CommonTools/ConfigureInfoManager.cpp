#include "StdAfx.h"
#include "ConfigureInfoManager.h"
#include "CommonStringFunction.h"
#include "GeneralFunctor.h"

#include <fstream>

namespace CommonTool
{

	shared_ptr<ConfigureInfoManager> ConfigureInfoManager::_instance;

	ConfigureInfoManager::ConfigureInfoManager(void):_configureFilename("ConfigureInfo.ini")
	{
	}


	ConfigureInfoManager::~ConfigureInfoManager(void)
	{
	}

	void ConfigureInfoManager::UpdateConfigure()
	{
		_infos.clear();

		ifstream in(_configureFilename);

		string line="";
		while(getline(in,line))
		{
			if(line!="")
			{
				CommonTool::TrimBeginEndBlank(line);

				ConfigureInfo info;
				info.message=line;
				_infos.push_back(info);
			}
		}

		in.close();
	}

	bool ConfigureInfoManager::HasTag( const string tag ) const
	{
		CREATE_FUNCTOR_IR(SameCfgInfo,string,ConfigureInfo,bool,
			if(input.message==_init)
			{
				return true;
			}
			else
			{
				return false;
			}
			);
			
		vector<ConfigureInfo>::const_iterator sameIt=find_if(_infos.begin(),_infos.end(),SameCfgInfo(tag));
		if(sameIt==_infos.end())
		{
			return false;
		}
		else
		{
			return true;
		}

	}

}

