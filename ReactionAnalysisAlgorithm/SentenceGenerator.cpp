#include "StdAfx.h"
#include "SentenceGenerator.h"

#include "../MindInterface/iCerebrum.h"
#include "../MindInterface/iConcept.h"
#include "../MindInterface/iConceptChain.h"
#include "../MindElement/CommonFunction.h"

#include "../Mathmatic/MathTool.h"
#include "../Mathmatic/Rand.h"

#include "../DataCollection/GrammaPattern.h"
#include "../DataCollection/Sentence.h"

using namespace Mind;
using namespace DataCollection;
using namespace Math;

SentenceGenerator::SentenceGenerator(void):_brain(iCerebrum::Instance())
{
}


SentenceGenerator::~SentenceGenerator(void)
{
}

void SentenceGenerator::Generate( const vector<shared_ptr<Mind::iConceptChain>>& hyperChains )
{
	ofstream out("DebugInfo//Chain Grammar Info.txt");
	
	vector<SentenceInfo> sentenceInfo;
	sentenceInfo.reserve(hyperChains.size());
	for (unsigned int i=0;i<hyperChains.size();++i)
	{
		GrammarPattern pattern=ChainToPattern(hyperChains[i]);
		vector<GrammarPattern> subPatterns=_brain->ContainSubsequence(pattern);
		SentenceInfo info;
		info.hyperChain=hyperChains[i];
		info.patternFreq=ComputeTotalFreq(subPatterns);
		sentenceInfo.push_back(info);

		OutputChainAndPatternInfo(hyperChains[i],subPatterns,out);
	}

	vector<SentenceInfo> selectedInfos=SelectHyperChainsOfMaxFreq(sentenceInfo);
	int selectedIndex=Rand::GetRandInt(0,selectedInfos.size()-1);
	_sentence=ChainToSentence(selectedInfos[selectedIndex].hyperChain);
}

DataCollection::GrammarPattern SentenceGenerator::ChainToPattern( const shared_ptr<Mind::iConceptChain> chain ) const
{
	vector<shared_ptr<iConcept>> conceptVec=chain->GetConceptVec();
	vector<PartOfSpeech> pos;
	pos.reserve(conceptVec.size());

	for (unsigned int i=0;i<conceptVec.size();++i)
	{
		pos.push_back(conceptVec[i]->GetPartOfSpeech());
	}

	return GrammarPattern(pos);
}

void SentenceGenerator::OutputChainAndPatternInfo( 
	const shared_ptr<Mind::iConceptChain> chain, 
	const vector<DataCollection::GrammarPattern>& patterns, 
	ofstream& out ) const
{
	out<<"HyperChain: "<<endl;
	CommonFunction::WriteConcepts(chain->GetConceptVec(),out);
	out<<"Grammar pattern count: "<<ComputeTotalFreq(patterns)<<endl;

}

int SentenceGenerator::ComputeTotalFreq( const vector<DataCollection::GrammarPattern>& patterns ) const
{
	int freq_sum(0);
	for (unsigned int j=0;j<patterns.size();++j)
	{
		freq_sum+=_brain->GetFreqencyofPattern(patterns[j]);
	}

	return freq_sum;
}

vector<SentenceGenerator::SentenceInfo> SentenceGenerator::SelectHyperChainsOfMaxFreq( const vector<SentenceInfo>& hyperChainInfos ) const
{
	class Compare_Info
	{
	public:
		bool operator()(const SentenceInfo& left,const SentenceInfo& right)
		{
			return left.patternFreq<right.patternFreq;
		}
	};

	double maxFreq=max_element(hyperChainInfos.begin(),hyperChainInfos.end(),Compare_Info())->patternFreq;

	class FindHyperChainInfos
	{
		double _level;
		vector<SentenceGenerator::SentenceInfo> _infos;
	public:
		FindHyperChainInfos(const double val):_level(val){}
		~FindHyperChainInfos(){}
		void operator()(const SentenceInfo& info)
		{
			if(Math::DoubleCompare(info.patternFreq,_level)==0)
			{
				_infos.push_back(info);
			}
		}
		vector<SentenceGenerator::SentenceInfo> GetResult()const {return _infos;}
	};

	FindHyperChainInfos findInfos(maxFreq);
	findInfos=for_each(hyperChainInfos.begin(),hyperChainInfos.end(),findInfos);

	return findInfos.GetResult();
}

shared_ptr<DataCollection::Sentence> SentenceGenerator::ChainToSentence( const shared_ptr<Mind::iConceptChain> chain ) const
{
	vector<shared_ptr<iConcept>> conceptVec=chain->GetConceptVec();

	string sen="";
	for (unsigned int i=0;i<conceptVec.size();++i)
	{
		sen+=conceptVec[i]->GetString();
	}

	return shared_ptr<Sentence>(new Sentence(sen));
}

// void SentenceGenerator::SearchPossibleSentenceCombination(const SentenceInfo& centerSentence,
// 	const vector<SentenceInfo>& otherSentence)
// {
// 	for (unsigned int i=0;i<otherSentence.size();++i)
// 	{
// 
// 	}
// }
