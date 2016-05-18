#include "StdAfx.h"
#include "Punctuator.h"
#include "../DataCollection/Character.h"
#include "../DataCollection/Sentence.h"
#include "../DataCollection/LanguageFunc.h"

using namespace DataCollection;
using namespace std;

Punctuator::Punctuator(std::string longSen):_unpunctuated(new Sentence(longSen))
{
}


Punctuator::~Punctuator(void)
{
}

bool Punctuator::Punctuate( shared_ptr<DataCollection::Sentence>& punctuated )
{
	vector<shared_ptr<Character>> unpun=_unpunctuated->GetRawSentence();

	if(unpun.empty())
		return false;
	vector<shared_ptr<Character>>::iterator sen_it=unpun.begin();
	do 
	{
		vector<shared_ptr<Character>>::iterator chara_it=find_if(sen_it,unpun.end(),LanguageFunc::IsPuncEndofSentence);

		if(chara_it==unpun.end()) //if there is no punctuation in the end
		{
			vector<shared_ptr<Character>> aSen(sen_it,chara_it);
			punctuated->AddSubSentence(aSen);
			break;
		}

		//find the next character which is not a punctuation
		do 
		{
			++chara_it;
			if(chara_it==unpun.end())
			{
				vector<shared_ptr<Character>> aSen(sen_it,chara_it);
				punctuated->AddSubSentence(aSen);
				break;
			}
			else if(LanguageFunc::IsPuncEndofSentence(*chara_it)||LanguageFunc::IsPuncRightside(*chara_it))
				continue;
			else 
			{
				vector<shared_ptr<Character>> aSen(sen_it,chara_it);
				punctuated->AddSubSentence(aSen);
				sen_it=chara_it;
				break;
			}

		} while (chara_it!=unpun.end());
		if(chara_it==unpun.end())
			break;

	} while (sen_it!=unpun.end());

	return true;
}
