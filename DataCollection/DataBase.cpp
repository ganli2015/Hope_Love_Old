#include "StdAfx.h"
#include "DataBase.h"
#include "ChineseCharacters.h"
#include "Punctures.h"
#include "Character.h"
using namespace std;



namespace DataCollection
{
// 	const shared_ptr<ChineseCharacters> DataBase::_chinesecharacters=shared_ptr<ChineseCharacters>(new ChineseCharacters());
// 	const shared_ptr<WordColletction> DataBase::_wordCollection(new WordColletction());
// 	const shared_ptr<Punctures> DataBase::_punctures(new Punctures());

	DataBase* DataBase::_pDataBase=NULL;

	DataBase::DataBase(void):_chinesecharacters(new ChineseCharacters()),
		_punctures(new Punctures())
	{
	}

	DataBase::~DataBase(void)
	{
	}

	bool DataBase::IsPuncEndofSentence( shared_ptr<Character> val ) const
	{
		return _punctures->IsPuncEndofSentence(val);
	}

	bool DataBase::IsPuncRightside( shared_ptr<Character> val ) const
	{
		return _punctures->IsPuncRightside(val);
	}

	DataBase* DataBase::GetInstance()
	{
		
		if(_pDataBase==NULL)
			_pDataBase=new DataBase();
		return _pDataBase;

	}

}

