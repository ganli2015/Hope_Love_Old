#pragma once
#include "InOut.h"

namespace Mind
{
	class Concept;
	class Cerebrum;
	class ConceptChain;
	struct ConceptChainProperty;
}

class ChainAnalyzer
{
private:
	struct HyperChainInfo
	{
		shared_ptr<Mind::ConceptChain> hyperChain;
		double baseChainConfidence;
		double meanLevel;
	};

	Mind::Cerebrum* _brain;

	vector<HyperChainInfo> _hyperChainInfos;
public:
	ChainAnalyzer(void);
	~ChainAnalyzer(void);

	void Analyze(const vector<Mind::ConceptChainProperty>& baseChains);

	vector<shared_ptr<Mind::ConceptChain>> GetHyperChains() const;
	
private:
	void ComputeHyperChains(const shared_ptr<Mind::ConceptChain> baseChain,vector<shared_ptr<Mind::ConceptChain>>& hyperChains);
	vector<shared_ptr<Mind::ConceptChain>> ComputeProperCombination(const vector<shared_ptr<Mind::Concept>>& combination,const shared_ptr<Mind::ConceptChain> chain) const;
	//��������startIndex��ʼ��checkChain�ж��ٸ�Concept��testChain���Ӽ���
	int OverlappedCount(const int startIndex,const vector<shared_ptr<Mind::Concept>>& checkChain,const vector<shared_ptr<Mind::Concept>>& testChain) const;
	bool CoverBase(const vector<shared_ptr<Mind::Concept>>& hyperChain,const shared_ptr<Mind::ConceptChain>& baseChain) const;
	void ComputeHyperChainLevels(const vector<shared_ptr<Mind::ConceptChain>>& hyperChains,const shared_ptr<Mind::ConceptChain> baseChain,vector<double>& levels) const;
	//����hyperChain��ÿ��Concept��baseChain��level��Ȼ��ȡƽ��ֵ��
	static double ComputeHyperChainMeanLevel(const shared_ptr<Mind::ConceptChain> hyperChain,const shared_ptr<Mind::ConceptChain> baseChain);
	vector<ChainAnalyzer::HyperChainInfo> AssembleHyperChainInfo(const vector<shared_ptr<Mind::ConceptChain>>& hyperChains,
		const vector<double>& levels,
		const double confidence);
	//�ҳ����level���Ǽ���HyperChainInfo
	vector<ChainAnalyzer::HyperChainInfo> SelectHyperChainsOfMaxLevels(const vector<HyperChainInfo>& hyperChainInfos) const;

	void OutputHyperChains(const vector<HyperChainInfo>& hyperChainInfos,const shared_ptr<Mind::ConceptChain> baseChain,ofstream& out);
};

