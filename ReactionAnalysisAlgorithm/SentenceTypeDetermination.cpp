#include "stdafx.h"
#include "SentenceTypeDetermination.h"

#include "../DataCollection/Sentence.h"
#include "../DataCollection/Word.h"
#include "../DataCollection/LanguageFunc.h"

using namespace DataCollection;

std::vector<shared_ptr<DataCollection::Word>> SentenceTypeDetermination::_interrogativePronouns;

std::vector<shared_ptr<DataCollection::Word>> SentenceTypeDetermination::_linkVerb;

SentenceTypeDetermination::SentenceTypeDetermination()
{
	if(_interrogativePronouns.empty() || _linkVerb.empty())
	{
		_interrogativePronouns.clear();
		_linkVerb.clear();

		InitMyWords();
	}
}


SentenceTypeDetermination::~SentenceTypeDetermination()
{
}

SentenceTypeDetermination::Type SentenceTypeDetermination::Determine(const shared_ptr<DataCollection::Sentence> sen)
{
	if(IsInterrogative(sen))
	{
		return Interrogative;
	}
	else
	{
		return Declarative;
	}
}

void SentenceTypeDetermination::InitMyWords()
{
	//Initialize interrogative pronouns.
	_interrogativePronouns.push_back(shared_ptr<pronoun>(new pronoun("多少")));
	_interrogativePronouns.push_back(shared_ptr<pronoun>(new pronoun("几")));

	//Initialize link verbs.
	_linkVerb.push_back(shared_ptr<verb>(new verb("是")));
	_linkVerb.push_back(shared_ptr<verb>(new verb("等于")));
}

bool SentenceTypeDetermination::IsInterrogative(const shared_ptr<DataCollection::Sentence> sen)
{
	//Find the index of interrogative pronoun in <sen>.
	int interrogativeIndex = -1;
	for (unsigned int i=0;i<sen->GrammarWordCount();++i)
	{
		shared_ptr<Word> word = sen->GetGrammardWord(i);
		if(LanguageFunc::IndexOf(_interrogativePronouns,word)>=0)
		{
			interrogativeIndex = i;
		}
	}

	if(interrogativeIndex<=0)//If not find the interrogative pronoun or it is the beginning of the sentence, return false. 
	{
		return false;
	}

	//Check whether the previous word is a link verb.
	shared_ptr<Word> prevWord = sen->GetGrammardWord(interrogativeIndex - 1);
	if (LanguageFunc::IndexOf(_linkVerb, prevWord) >= 0)
	{
		_questionPart = ExtractQuetionPart(sen, interrogativeIndex - 1);
		return true;
	}
	else
	{
		return false;
	}
}

shared_ptr<DataCollection::Sentence> SentenceTypeDetermination::ExtractQuetionPart(const shared_ptr<DataCollection::Sentence> sen, const int linkVerbIndex)
{
	//Collect the words in the front of the link verb.
	string questionPartStr = "";
	vector<shared_ptr<Word>> questionPartWords;
	questionPartWords.reserve(linkVerbIndex);
	for (int i=0;i<linkVerbIndex;++i)
	{
		shared_ptr<Word> word = sen->GetGrammardWord(i);
		questionPartStr += word->GetString();
		questionPartWords.push_back(word);
	}

	shared_ptr<DataCollection::Sentence> res=make_shared<Sentence>(questionPartStr);
	res->SetGrammard(questionPartWords);

	return res;
}
