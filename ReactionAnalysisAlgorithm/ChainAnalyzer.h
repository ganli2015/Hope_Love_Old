#pragma once
#include "InOut.h"

namespace Mind
{
	class iConcept;
	class iCerebrum;
	class iConceptChain;
	struct ConceptChainProperty;
}

class ChainAnalyzer
{
private:
	///Hyper chains are chains based on some base chains.
	///<baseChainConfidence> is confidence of base chains.
	///<meanLevel> indicates how far hyper chains from base chains.
	struct HyperChainInfo
	{
		shared_ptr<Mind::iConceptChain> hyperChain;
		double baseChainConfidence;
		double meanLevel;
	};

	Mind::iCerebrum* _brain;

	vector<HyperChainInfo> _hyperChainInfos;
public:
	ChainAnalyzer(void);
	~ChainAnalyzer(void);

	///Analyze input chains <baseChains>.
	///And select optimal chains for reaction.
	///Optimal chains in general constitute of non-base concepts which are related with input base chains.
	void Analyze(const vector<Mind::ConceptChainProperty>& baseChains);

	vector<shared_ptr<Mind::iConceptChain>> GetHyperChains() const;
	
private:
	///Compute <hyperChains> from <baseChain>.
	void ComputeHyperChains(const shared_ptr<Mind::iConceptChain> baseChain,vector<shared_ptr<Mind::iConceptChain>>& hyperChains);
	///Compute proper hyper chains.
	///<combination> are collection of hyper concepts of each base concept in the base chain.
	///Each element of <combination> is collection of all backward concepts of the base concept.
	///<baseChain> is the base chain corresponding to <combination>.
	vector<shared_ptr<Mind::iConceptChain>> ComputeProperCombination(const vector<shared_ptr<Mind::iConcept>>& combination,const shared_ptr<Mind::iConceptChain> baseChain) const;
	///From the <startIndex>th concept of <checkChain> compute the longest continuous chain which is a sub chain of <testChain>.
	int OverlappedCount(const int startIndex,const vector<shared_ptr<Mind::iConcept>>& checkChain,const vector<shared_ptr<Mind::iConcept>>& testChain) const;
	///Check whether base concepts of <hyperChain> cover concepts in <baseChain>.
	bool CoverBase(const vector<shared_ptr<Mind::iConcept>>& hyperChain,const shared_ptr<Mind::iConceptChain>& baseChain) const;
	///Compute levels from <hyperchains> to <baseChain>.
	///Each level is recorded in <levels>.
	void ComputeHyperChainLevels(const vector<shared_ptr<Mind::iConceptChain>>& hyperChains,const shared_ptr<Mind::iConceptChain> baseChain,vector<double>& levels) const;
	///Compute the mean level from <hyperChain> to <baseChain>.
	static double ComputeHyperChainMeanLevel(const shared_ptr<Mind::iConceptChain> hyperChain,const shared_ptr<Mind::iConceptChain> baseChain);
	
	vector<ChainAnalyzer::HyperChainInfo> AssembleHyperChainInfo(const vector<shared_ptr<Mind::iConceptChain>>& hyperChains,
		const vector<double>& levels,
		const double confidence);
	///Select the hyper chains whose level are one of max in <hyperChainInfos>.
	vector<ChainAnalyzer::HyperChainInfo> SelectHyperChainsOfMaxLevels(const vector<HyperChainInfo>& hyperChainInfos) const;

	void OutputHyperChains(const vector<HyperChainInfo>& hyperChainInfos,const shared_ptr<Mind::iConceptChain> baseChain,ofstream& out);
};

