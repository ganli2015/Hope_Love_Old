#pragma once
#include <map>

namespace DataCollection
{
	class Character;
	class _DATACOLLECTIONINOUT ChineseCharacters : public MyObject
	{
       std::map<int,Character> _chinesecharacters;

	   void Initialize();
	public:
		ChineseCharacters(void);
		~ChineseCharacters(void);

		Character GetChara(int index);
	};
}


