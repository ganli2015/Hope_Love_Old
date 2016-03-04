#pragma once
#include "InOut.h"

namespace DataCollection
{
	class ChineseCharacters;
	class WordColletction;
	class Punctures;
	class Character;

	//Singleton
	class _DATACOLLECTIONINOUT DataBase
	{
		DataBase(void);
		~DataBase(void);
		DataBase(const DataBase&);

		static DataBase* _pDataBase;

		std::shared_ptr<ChineseCharacters> _chinesecharacters;
		std::shared_ptr<WordColletction> _wordCollection;
		std::shared_ptr<Punctures> _punctures;
	public:
		static DataBase*  GetInstance();
		

		//puncture
		bool IsPuncEndofSentence(shared_ptr<Character> val) const;
		bool IsPuncRightside(shared_ptr<Character> val) const;
	};

	
}



