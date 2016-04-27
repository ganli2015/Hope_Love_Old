#pragma once
#include "InOut.h"

namespace Mind
{
	class iCerebrum;
	class iConceptChain;
}

namespace DataCollection
{
	class GrammarPattern;
	class Sentence;
}

class SentenceGenerator
{
private:
	struct SentenceInfo
	{
		shared_ptr<Mind::iConceptChain> hyperChain;
		int patternFreq;
	};

	Mind::iCerebrum* _brain;

	shared_ptr<DataCollection::Sentence> _sentence;

public:
	SentenceGenerator(void);
	~SentenceGenerator(void);

	void Generate(const vector<shared_ptr<Mind::iConceptChain>>& hyperChains);
	shared_ptr<DataCollection::Sentence> GetSentence() const {return _sentence;}
private:
	DataCollection::GrammarPattern ChainToPattern(const shared_ptr<Mind::iConceptChain> chain) const;
	int ComputeTotalFreq(const vector<DataCollection::GrammarPattern>& patterns) const;
	vector<SentenceGenerator::SentenceInfo> SelectHyperChainsOfMaxFreq(const vector<SentenceInfo>& hyperChainInfos) const;
	shared_ptr<DataCollection::Sentence> ChainToSentence(const shared_ptr<Mind::iConceptChain> chain) const;

	void OutputChainAndPatternInfo(
		const shared_ptr<Mind::iConceptChain> chain,
		const vector<DataCollection::GrammarPattern>& patterns,
		ofstream& out) const;
};

