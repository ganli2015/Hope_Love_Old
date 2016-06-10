#pragma once
#include "InOut.h"

namespace CommonTool
{
	///Store configure information from configure file.
	class _COMMONTOOLSINOUT ConfigureInfoManager
	{
		static shared_ptr<ConfigureInfoManager> _instance;

		const string _configureFilename;

		struct ConfigureInfo
		{
			string message;
		};

		vector<ConfigureInfo> _infos;

	public:
		ConfigureInfoManager(void);
		~ConfigureInfoManager(void);

		static void SetInstance(const shared_ptr<ConfigureInfoManager> val){_instance=val;}
		static shared_ptr<ConfigureInfoManager> GetInstance() 
		{
			if(_instance==NULL)
			{
				_instance=shared_ptr<ConfigureInfoManager>(new ConfigureInfoManager());
			}
			return _instance;
		}

		void UpdateConfigure();
		bool HasTag(const string tag) const;

	private:

	};
}

#define CFG_SECTION(tag) if(CommonTool::ConfigureInfoManager::GetInstance()->HasTag(#tag))
#define CFG_IF(tag,trueBody,falseBody) \
	if(CommonTool::ConfigureInfoManager::GetInstance()->HasTag(#tag)) \
	{ \
		trueBody \
	} \
	else \
	{ \
		falseBody \
	} 

