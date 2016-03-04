#include "StdAfx.h"
#include "Character.h"
#include "Punctures.h"
#include "../CommonTools/CommonCompareFunction.h"

using namespace std;

namespace DataCollection
{
	Punctures::Punctures(void)
	{
		Initialize();
	}


	Punctures::~Punctures(void)
	{

	}

	void Punctures::Initialize()
	{
		_puncRightside.push_back(shared_ptr<Character>(new Character(string("¡±"))));
		_puncRightside.push_back(shared_ptr<Character>(new Character(string("¡¯"))));
		_puncRightside.push_back(shared_ptr<Character>(new Character(string(")"))));

		_puncEndofSentence.push_back(shared_ptr<Character>(new Character(string("¡£"))));
		_puncEndofSentence.push_back(shared_ptr<Character>(new Character(string("£¡"))));
		_puncEndofSentence.push_back(shared_ptr<Character>(new Character(string("£¿"))));
		_puncEndofSentence.push_back(shared_ptr<Character>(new Character(string("£º"))));
		_puncEndofSentence.push_back(shared_ptr<Character>(new Character(string("£»"))));
		_puncEndofSentence.push_back(shared_ptr<Character>(new Character(string("¡­¡­"))));

		_punctures.insert(_punctures.begin(),_puncRightside.begin(),_puncRightside.end());
		_punctures.insert(_punctures.begin(),_puncEndofSentence.begin(),_puncEndofSentence.end());
	}



	bool DataCollection::Punctures::IsPuncEndofSentence( shared_ptr<Character> val ) const
	{
		vector<shared_ptr<Character>>::const_iterator find_it=find_if(_puncEndofSentence.begin(),_puncEndofSentence.end(),CommonTool::comp_ptr<Character>(val));
		if(find_it!=_puncEndofSentence.end())
			return true;
		else return false;
	}

	bool DataCollection::Punctures::IsPuncRightside( shared_ptr<Character> val ) const
	{
		vector<shared_ptr<Character>>::const_iterator find_it=find_if(_puncRightside.begin(),_puncRightside.end(),CommonTool::comp_ptr<Character>(val));
		if(find_it!=_puncRightside.end())
			return true;
		else return false;
	}
}

