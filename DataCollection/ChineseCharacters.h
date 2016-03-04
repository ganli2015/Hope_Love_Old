#pragma once
#include <map>
#include "WordSearchAlgorithm.h"

namespace DataCollection
{
	class Character;
	class _DATACOLLECTIONINOUT ChineseCharacters
	{
       std::map<int,Character> _chinesecharacters;

	   void Initialize();
	public:
		ChineseCharacters(void);
		~ChineseCharacters(void);

		Character GetChara(int index);
	};
}


