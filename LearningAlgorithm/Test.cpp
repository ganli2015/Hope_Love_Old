#include "Stdafx.h"
#include "InOut.h"
#include "GrammarLearning.h"

#include "../DataCollection/Sentence.h"
#include "../DataCollection/Word.h"
#include "../DataCollection/DataBaseProcessorTool.h"

#include "../Mind/Cerebrum.h"

using namespace DataCollection;

class SampleSentence
{
public: 
	SampleSentence(){}
	~SampleSentence(){}

	static shared_ptr<DataCollection::Sentence> Generate()
	{
		shared_ptr<Word> w1(new pronoun("ÄªÄª"));
		shared_ptr<Word> w2(new pronoun("ÎÒ"));
		shared_ptr<Word> w3(new verb("°®"));
		shared_ptr<Word> w4(new pronoun("Äã"));
		shared_ptr<Word> w5(new puncture("£¡"));
		shared_ptr<Word> w6(new puncture("£¡"));
		vector<shared_ptr<Word>> words;
		words.push_back(w1);
		words.push_back(w2);
		words.push_back(w3);
		words.push_back(w4);
		words.push_back(w5);
		words.push_back(w6);
		shared_ptr<DataCollection::Sentence> sentence(new Sentence());
		sentence->SetGrammard(words);

		return sentence;
	}
};

vector<int> GetGrammarFrequence(const shared_ptr<DataCollection::Sentence> sentence)
{
	Mind::Cerebrum* brain=Mind::Cerebrum::Instance();

	vector<shared_ptr<Word>> words=DataBaseProcessorTool::RemovePuncs(sentence->GetGrammard());
	vector<GrammarPattern> matchedPatterns=brain->ContainSubsequence(DataBaseProcessorTool::ConvertToPattern(words));

	vector<int>  res;
	for (unsigned int i=0;i<matchedPatterns.size();++i)
	{
		res.push_back(brain->GetFreqencyofPattern(matchedPatterns[i]));
	}

	return res;
}

bool CheckFreqIncrease(const vector<int>& left,const vector<int>& right)
{
	if(left.size()!=right.size())
	{
		return false;
	}

	for (unsigned int i=0;i<left.size();++i)
	{
		if(left[i]!=right[i]-1)
		{
			return false;
		}
	}

	return true;
}

int __cdecl main()
{
	shared_ptr<DataCollection::Sentence> sentence=SampleSentence::Generate();
	vector<int> freq_before=GetGrammarFrequence(sentence);
	GrammarLearning::AdjustGrammarPatternFrequency(sentence);
	vector<int> freq_after=GetGrammarFrequence(sentence);
	assert(CheckFreqIncrease(freq_before,freq_after));


	return 0;
}

