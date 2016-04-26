#pragma once
#include "InOut.h"

namespace Mind
{
	class iCerebrum;
	class ConceptChain;
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
		shared_ptr<Mind::ConceptChain> hyperChain;
		int patternFreq;
	};

	Mind::iCerebrum* _brain;

	shared_ptr<DataCollection::Sentence> _sentence;

public:
	SentenceGenerator(void);
	~SentenceGenerator(void);

	void Generate(const vector<shared_ptr<Mind::ConceptChain>>& hyperChains);
	shared_ptr<DataCollection::Sentence> GetSentence() const {return _sentence;}
private:
	DataCollection::GrammarPattern ChainToPattern(const shared_ptr<Mind::ConceptChain> chain) const;
	int ComputeTotalFreq(const vector<DataCollection::GrammarPattern>& patterns) const;
	vector<SentenceGenerator::SentenceInfo> SelectHyperChainsOfMaxFreq(const vector<SentenceInfo>& hyperChainInfos) const;
	shared_ptr<DataCollection::Sentence> ChainToSentence(const shared_ptr<Mind::ConceptChain> chain) const;

	void OutputChainAndPatternInfo(
		const shared_ptr<Mind::ConceptChain> chain,
		const vector<DataCollection::GrammarPattern>& patterns,
		ofstream& out) const;
};

