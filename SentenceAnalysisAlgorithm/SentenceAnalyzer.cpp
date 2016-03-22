#include "StdAfx.h"
#include "SentenceAnalyzer.h"
#include "Punctuator.h"
#include "WordSegmentator.h"
#include "GrammarAnalyzer.h"
#include "StructureAnalyzer.h"
#include "WordRelationTableBuilder.h"

#include "../CommonTools/CommonTranslateFunction.h"
#include "../DataCollection/DataBaseProcessorTool.h"
#include "../DataCollection/Character.h"
#include "../DataCollection/Sentence.h"
#include "../DataCollection/Word.h"

#include "../Mind/Cerebrum.h"
#include "../Mind/Concept.h"

#include <iostream>

using namespace std;
using namespace DataCollection;
 

SentenceAnalyzer::SentenceAnalyzer(void)
{
}

SentenceAnalyzer::SentenceAnalyzer(std::string sen):_rawSentenceString(sen)
{
	
}

SentenceAnalyzer::~SentenceAnalyzer(void)
{
	//DeleteVectorPtr(_punctuated);
}

void SentenceAnalyzer::Analyze()
{
	Mind::Cerebrum* brain=Mind::Cerebrum::Instance();

	Punctuator punctuator(_rawSentenceString);
	std::vector<shared_ptr<DataCollection::Sentence>> punctuated;
	punctuator.Punctuate(punctuated);

	WordSegmentator wordsegmentor;
	for (unsigned int i=0;i<punctuated.size();++i)
	{
		wordsegmentor.Segment(punctuated[i]);
	}

	vector<shared_ptr<Sentence>> subSentences;
	for (unsigned int i=0;i<punctuated.size();++i)
	{
		GrammarAnalyzer grammarAnalyzer(punctuated[i]);
		grammarAnalyzer.Analyze();
		subSentences.push_back(grammarAnalyzer.GetResult());
	}

#ifdef _DEBUG //测试GrammarAnalyzer
	for (unsigned int i=0;i<subSentences.size();++i)
	{
		cout<<"The raw sentence is "<<DataBaseProcessorTool::ConvertCharacterToString(subSentences[i]->GetRawSentence())<<endl;
		Cout_GrammardSentence(subSentences[i]);
	}
#endif // _DEBUG

	for (unsigned int i=0;i<subSentences.size();++i)
	{
		StructureAnalyzer structureAnalyzer(subSentences[i]);
		structureAnalyzer.Analyze();
		//subSentences[i]=structureAnalyzer.GetResult();
	}

#ifdef _DEBUG //测试StructureAnalyzer
	for (unsigned int i=0;i<subSentences.size();++i)
	{
		cout<<"The raw sentence is "<<DataBaseProcessorTool::ConvertCharacterToString(subSentences[i]->GetRawSentence())<<endl;
		Cout_WordConnectionIntensity(subSentences[i]);
	}
#endif

	for (unsigned int i=0;i<subSentences.size();++i)
	{
		WordRelationTableBuilder wordRelationTableBuilder(subSentences[i]);
		wordRelationTableBuilder.Build();
	}

#ifdef _DEBUG //测试WordRelationTableBuilder
	Cout_WordRelations();
#endif

	//统计不认识的词语
	_unknownWords=CountUnknownWords(subSentences);

	_analyzedSentences=subSentences;
}

void SentenceAnalyzer::Cout_GrammardSentence(const shared_ptr<Sentence> grammard)
{
	for (unsigned int i=0;i<grammard->Count_Grammard();++i)
	{
		vector<shared_ptr<Word>> instance=grammard->GetGrammard(i);
		cout<<"Grammar "<<i<<":"<<endl;

		for(unsigned int j=0;j<instance.size();++j)
		{
			shared_ptr<Word> word=instance[j];
			cout<<word->GetString()<<" :"<<word->Type()<<endl;
		}
	}
	
	cout<<endl;

}

void SentenceAnalyzer::Cout_WordConnectionIntensity( const shared_ptr<DataCollection::Sentence> sentence )
{
	for (unsigned int i=0;i<sentence->Count_Grammard();++i)
	{
		cout<<"Structure "<<i<<":"<<endl;

		int wordCount=sentence->GrammarWordCount(i);
		for (int j=0;j<wordCount;++j)
		{
			for (int k=0;k<wordCount;++k)
			{
				cout<<sentence->GetWordIntensity(i,j,k)<<" ";
			}
			cout<<endl;
		}
	}

	cout<<endl;
}

void SentenceAnalyzer::Cout_WordRelations()
{
	Mind::Cerebrum* brain=Mind::Cerebrum::Instance();
	vector<pair<shared_ptr<Mind::Concept>,shared_ptr<Mind::Concept>>> relations=brain->GetAllInteractPairs();

	cout<<"Test Word Relations"<<endl;

	for (unsigned int i=0;i<relations.size();++i)
	{
		cout<<relations[i].first->GetString();
		cout<<" ";
		cout<<relations[i].second->GetString();
		cout<<endl;
	}

	cout<<endl;
}

vector<shared_ptr<DataCollection::Word>> SentenceAnalyzer::CountUnknownWords( const vector<shared_ptr<Sentence>>& sentences ) const
{
	Mind::Cerebrum* brain=Mind::Cerebrum::Instance();

	vector<shared_ptr<DataCollection::Word>> res;

	for (unsigned int i=0;i<sentences.size();++i)
	{
		vector<shared_ptr<Word>> words=sentences[i]->GetGrammard(0);
		for (unsigned int j=0;j<words.size();++j)
		{
			if(!brain->IsInMind(words[j]))
			{
				res.push_back(words[j]);
			}
		}
	}

	return res;
}
