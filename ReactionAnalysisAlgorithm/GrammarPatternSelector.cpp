#include "StdAfx.h"
#include "GrammarPatternSelector.h"

#include "../DataCollection/GrammaPattern.h"
#include "../DataCollection/Sentence.h"
#include "../DataCollection/LanguageFunc.h"

#include "../Mathmatic/Rand.h"

#include "../MindInterface/iCerebrum.h"

#include <time.h>
#include <iostream>

using namespace DataCollection;

GrammarPatternSelector::GrammarPatternSelector(void)
{
}


GrammarPatternSelector::~GrammarPatternSelector(void)
{
}

DataCollection::GrammarPattern GrammarPatternSelector::SelectReactPattern( const shared_ptr<DataCollection::Sentence> sen )
{
	Mind::iCerebrum *brain=Mind::iCerebrum::Instance();

	vector<shared_ptr<Word>> words=LanguageFunc::RemovePuncs(sen->GetGrammard());
	vector<GrammarPattern> matchedPatterns=brain->ContainSubsequence(LanguageFunc::ConvertToPattern(words));
	//找到所有包含<matchedPatterns>的patterns
	vector<GrammarPattern> totalParentPatterns=GetParentPatterns(matchedPatterns);
	
	//频率作为权重，随机选择一个pattern
	vector<double> frequency=GetPatternFrequency(totalParentPatterns);
	int randIndex=Math::Rand::GetRandInt(frequency);
	GrammarPattern randPattern=totalParentPatterns[randIndex];



	vector<shared_ptr<Word>> randWords;
	vector<PartOfSpeech> pos=randPattern.GetPattern();
	for (unsigned int i=0;i<pos.size();++i)
	{
		vector<shared_ptr<DataCollection::Word>> words=brain->GetAllWordsOfPOS(pos[i]);
		int randIndex=rand()%(words.size());
		randWords.push_back(words[randIndex]);
	}

	for (unsigned int i=0;i<randWords.size();++i)
	{
		cout<<randWords[i]->GetString();
	}

	return GrammarPattern();
}

vector<DataCollection::GrammarPattern> GrammarPatternSelector::GetParentPatterns( const vector<DataCollection::GrammarPattern>& patterns )
{
	Mind::iCerebrum *brain=Mind::iCerebrum::Instance();

	class NotInVector
	{
		vector<GrammarPattern> _vec;
	public:
		NotInVector(const vector<GrammarPattern>& vec):_vec(vec){}
		~NotInVector(){}

		bool operator()(const GrammarPattern& pattern)
		{
			if(find(_vec.begin(),_vec.end(),pattern)==_vec.end())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	};

	vector<GrammarPattern> totalParentPatterns;
	for (unsigned int i=0;i<patterns.size();++i)
	{
		vector<GrammarPattern> parentPatterns=brain->ContainedSubsequence(patterns[i]);
		//把parentPatterns拷贝到totalParentPatterns，去掉重复的。
		copy_if(parentPatterns.begin(),parentPatterns.end(),back_inserter(totalParentPatterns),NotInVector(totalParentPatterns));
	}

	return totalParentPatterns;
}

vector<double> GrammarPatternSelector::GetPatternFrequency( const vector<DataCollection::GrammarPattern>& patterns )
{
	class QueryFrequency
	{
		Mind::iCerebrum* _brain;
	public:
		QueryFrequency()
		{
			_brain=Mind::iCerebrum::Instance();
		}
		~QueryFrequency(){}

		double operator()(const GrammarPattern& pattern)
		{
			return _brain->GetFreqencyofPattern(pattern);
		}
	};

	vector<double> res;
	transform(patterns.begin(),patterns.end(),back_inserter(res),QueryFrequency());

	return res;
}
