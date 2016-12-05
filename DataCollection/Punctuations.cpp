#include "StdAfx.h"
#include "Character.h"
#include "Punctuations.h"
#include "../CommonTools/CommonCompareFunction.h"

using namespace std;

namespace DataCollection
{
	Punctuations::Punctuations(void)
	{
		Initialize();
	}


	Punctuations::~Punctuations(void)
	{

	}

	void Punctuations::Initialize()
	{
		//Prepare two kind of punctuations and both of them append to <_punctures>.
		//They are not complete.
		_puncRightside.push_back(shared_ptr<Character>(new Character(string("¡±"))));
		_puncRightside.push_back(shared_ptr<Character>(new Character(string("¡°"))));
		_puncRightside.push_back(shared_ptr<Character>(new Character(string("¡¯"))));
		_puncRightside.push_back(shared_ptr<Character>(new Character(string(")"))));
		_puncRightside.push_back(shared_ptr<Character>(new Character(string("£¯"))));

		_puncEndofSentence.push_back(shared_ptr<Character>(new Character(string("¡£"))));
		_puncEndofSentence.push_back(shared_ptr<Character>(new Character(string("£¡"))));
		_puncEndofSentence.push_back(shared_ptr<Character>(new Character(string("£¿"))));
		_puncEndofSentence.push_back(shared_ptr<Character>(new Character(string("£º"))));
		_puncEndofSentence.push_back(shared_ptr<Character>(new Character(string("£»"))));
		_puncEndofSentence.push_back(shared_ptr<Character>(new Character(string("¡­¡­"))));
		_puncEndofSentence.push_back(shared_ptr<Character>(new Character(string("£¬"))));

		_punctures.insert(_punctures.begin(),_puncRightside.begin(),_puncRightside.end());
		_punctures.insert(_punctures.begin(),_puncEndofSentence.begin(),_puncEndofSentence.end());
	}



	bool DataCollection::Punctuations::IsPuncEndofSentence( shared_ptr<Character> val ) const
	{
		vector<shared_ptr<Character>>::const_iterator find_it=find_if(_puncEndofSentence.begin(),_puncEndofSentence.end(),CommonTool::comp_ptr<Character>(val));
		if(find_it!=_puncEndofSentence.end())
			return true;
		else return false;
	}

	bool DataCollection::Punctuations::IsPuncRightside( shared_ptr<Character> val ) const
	{
		vector<shared_ptr<Character>>::const_iterator find_it=find_if(_puncRightside.begin(),_puncRightside.end(),CommonTool::comp_ptr<Character>(val));
		if(find_it!=_puncRightside.end())
			return true;
		else return false;
	}
}

