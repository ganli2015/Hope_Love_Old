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

		///Get unique instance of ConfigureInfoManager.
		static shared_ptr<ConfigureInfoManager> GetInstance() 
		{
			if(_instance==NULL)
			{
				_instance=shared_ptr<ConfigureInfoManager>(new ConfigureInfoManager());
			}
			return _instance;
		}

		///Read from configure file again and refresh configure information in <me>.
		void UpdateConfigure();
		///Check whether there is configure information <tag> in <me>.
		bool HasTag(const string tag) const;

	private:
		
	};
}

///If there is <tag> in the configure file ,then do...
#define CFG_SECTION(tag) if(CommonTool::ConfigureInfoManager::GetInstance()->HasTag(#tag))
///If there is <tag> in the configure file ,then do <trueBody>,otherwise <falseBody>.
#define CFG_IF(tag,trueBody,falseBody) \
	if(CommonTool::ConfigureInfoManager::GetInstance()->HasTag(#tag)) \
	{ \
		trueBody \
	} \
	else \
	{ \
		falseBody \
	} 

