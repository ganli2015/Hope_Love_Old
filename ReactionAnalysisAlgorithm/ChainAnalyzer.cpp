#include "StdAfx.h"
#include "ChainAnalyzer.h"
#include "ExtractConceptChains.h"

#include "../Mathmatic/MathTool.h"
#include "../Mathmatic/FindSequence.h"

#include "../Mind/Cerebrum.h"
#include "../Mind/Concept.h"
#include "../Mind/ConceptChain.h"
#include "../Mind/CommonFunction.h"
#include "../Mind/ConceptLevelTable.h"

using namespace Mind;
using namespace Math;

ChainAnalyzer::ChainAnalyzer(void):_brain(Cerebrum::Instance())
{
}


ChainAnalyzer::~ChainAnalyzer(void)
{
}

void ChainAnalyzer::Analyze(const vector<Mind::ConceptChainProperty>& baseChains)
{
	ofstream out("DebugInfo//HyperChains.txt");
	for (unsigned int i=0;i<baseChains.size();++i)
	{
		ConceptChainProperty property=baseChains[i];
		vector<shared_ptr<ConceptChain>> hyperChains;
		ComputeHyperChains(property.chain,hyperChains);
		vector<double> levels;
		ComputeHyperChainLevels(hyperChains,baseChains[i].chain,levels);
		vector<HyperChainInfo> hyperInfos=AssembleHyperChainInfo(hyperChains,levels,property.confidence);


#ifdef _DEBUG
		OutputHyperChains(hyperInfos,baseChains[i].chain,out);
#endif // _DEBUG

		vector<HyperChainInfo> selectedHyperInfos=SelectHyperChainsOfMaxLevels(hyperInfos);

		_hyperChainInfos.insert(_hyperChainInfos.end(),selectedHyperInfos.begin(),selectedHyperInfos.end());
	}


}

void ChainAnalyzer::ComputeHyperChains( const shared_ptr<ConceptChain> baseChain,vector<shared_ptr<ConceptChain>>& hyperChains )
{
	vector<shared_ptr<Concept>> conceptSequence=baseChain->GetConceptVec();

	vector<vector<shared_ptr<Concept>>> backwardConceptSequence;//存放所有backward concept的容器，第i个元素表示conceptSequence的第i个concept的所有backward concept。
	backwardConceptSequence.reserve(conceptSequence.size());
	for (unsigned int i=0;i<conceptSequence.size();++i)
	{
		vector<shared_ptr<Concept>> backConcepts=_brain->SearchBackwardConcepts(conceptSequence[i]);
		backConcepts.push_back(conceptSequence[i]);
		backwardConceptSequence.push_back(backConcepts);
	}

	//所有backward concept的可能组合序列
	vector<vector<shared_ptr<Concept>>> combinations=Math::GetAllCombinations<shared_ptr<Concept>>::Get(backwardConceptSequence);
	for (unsigned int i=0;i<combinations.size();++i)
	{
		vector<shared_ptr<ConceptChain>> properCombi=ComputeProperCombination(combinations[i],baseChain);
		hyperChains.insert(hyperChains.end(),properCombi.begin(),properCombi.end());
	}
}

vector<shared_ptr<ConceptChain>> ChainAnalyzer::ComputeProperCombination( const vector<shared_ptr<Mind::Concept>>& combination,const shared_ptr<Mind::ConceptChain> baseChain ) const
{
	vector<shared_ptr<ConceptChain>> res;

	vector<vector<shared_ptr<Concept>>> subSequences=GetAllSubSequence<shared_ptr<Concept>>::Get(combination);
	for (unsigned int i=0;i<subSequences.size();++i)
	{
		if(CoverBase(subSequences[i],baseChain))
		{
			res.push_back(shared_ptr<ConceptChain>(new ConceptChain(subSequences[i])));
		}
	}

	return res;
}

bool ChainAnalyzer::CoverBase(const vector<shared_ptr<Concept>>& hyperChain,const shared_ptr<ConceptChain>& baseChain) const
{
	typedef pair<shared_ptr<Mind::Concept>,shared_ptr<Mind::Concept>> ConceptPair;

	//计算两两Concept之间的相互作用，得到所有相互作用对。
	vector<ConceptPair> allPairs;
	for (unsigned int i=0;i<hyperChain.size()-1;++i)
	{
		vector<ConceptPair> basePairs;
		hyperChain[i]->DeepInteractWith(hyperChain[i+1],basePairs);
		allPairs.insert(allPairs.end(),basePairs.begin(),basePairs.end());
	}

	//对allPairs提取所有的Concept Chain。
	vector<shared_ptr<ConceptChain>> chains=ExtractConceptChains::Extract(allPairs);
	for (unsigned int i=0;i<chains.size();++i)
	{
		if(baseChain->IsSubSequenceOf(chains[i]))
		{
			return true;
		}
	}
	return false;
}

int ChainAnalyzer::OverlappedCount( const int startIndex,const vector<shared_ptr<Concept>>& checkChain,const vector<shared_ptr<Concept>>& testChain ) const
{
	int count=0;
	for (unsigned int i=startIndex;i<checkChain.size();++i)
	{
		if(CommonFunction::IndexOf(testChain,checkChain[i])>=0)//checkChain[i]是testChain的一个元素。
		{
			count++;
		}
		else
		{
			break;
		}
	}

	return count;
}

void ChainAnalyzer::OutputHyperChains( const vector<HyperChainInfo>& hyperChainInfos,const shared_ptr<Mind::ConceptChain> baseChain,ofstream& out )
{
	if(hyperChainInfos.empty()) return;

	out<<"Base Chain: "<<endl;
	CommonFunction::WriteConcepts(baseChain->GetConceptVec(),out);
	out<<"Confidence: "<<hyperChainInfos[0].baseChainConfidence<<endl;
	out<<"HyperChains: "<<endl;
	for (unsigned int i=0;i<hyperChainInfos.size();++i)
	{
		CommonFunction::WriteConcepts(hyperChainInfos[i].hyperChain->GetConceptVec(),out);
		out<<"Level: "<<hyperChainInfos[i].meanLevel<<endl;
	}
	out<<endl;
}

void ChainAnalyzer::ComputeHyperChainLevels( const vector<shared_ptr<ConceptChain>>& hyperChains,const shared_ptr<Mind::ConceptChain> baseChain,vector<double>& levels ) const
{
	class ComputeLevel
	{
		shared_ptr<Mind::ConceptChain> _baseChain;
	public:
		ComputeLevel(const shared_ptr<Mind::ConceptChain> val):_baseChain(val){}
		~ComputeLevel(){}
		double operator()(const shared_ptr<Mind::ConceptChain> hyperChain)
		{
			return ChainAnalyzer::ComputeHyperChainMeanLevel(hyperChain,_baseChain);
		}
	};

	levels.clear();
	levels.reserve(hyperChains.size());
	transform(hyperChains.begin(),hyperChains.end(),back_inserter(levels),ComputeLevel(baseChain));
}

double ChainAnalyzer::ComputeHyperChainMeanLevel( const shared_ptr<Mind::ConceptChain> hyperChain,const shared_ptr<Mind::ConceptChain> baseChain )
{
	vector<shared_ptr<Concept>> hyperConcepts=hyperChain->GetConceptVec();
	vector<shared_ptr<Concept>> baseConcepts=baseChain->GetConceptVec();
	vector<int> levels;
	for (unsigned int i=0;i<hyperConcepts.size();++i)
	{
		shared_ptr<ConceptLevelTable> levelTable=hyperConcepts[i]->GetLevelTable();
		int minLevel=BigInt;
		//选择与baseConcepts的最小level作为hyperConcepts[i]的level。
		for (unsigned int j=0;j<baseConcepts.size();++j)
		{
			int level=levelTable->LevelTo(baseConcepts[j]);
			if(level>=0 && level<minLevel)
			{
				minLevel=level;
			}
		}
		Check(minLevel!=BigInt);

		levels.push_back(minLevel);
	}

	return MeanValue(levels);
}

vector<ChainAnalyzer::HyperChainInfo> ChainAnalyzer::AssembleHyperChainInfo( const vector<shared_ptr<Mind::ConceptChain>>& hyperChains, const vector<double>& levels, const double confidence )
{
	vector<HyperChainInfo> res;
	res.reserve(hyperChains.size());

	Check(hyperChains.size()==levels.size());
	for (unsigned int i=0;i<hyperChains.size();++i)
	{
		HyperChainInfo info;
		info.hyperChain=hyperChains[i];
		info.meanLevel=levels[i];
		info.baseChainConfidence=confidence;
		res.push_back(info);
	}

	return res;
}

vector<ChainAnalyzer::HyperChainInfo> ChainAnalyzer::SelectHyperChainsOfMaxLevels( const vector<HyperChainInfo>& hyperChainInfos ) const
{
	class Compare_Info
	{
	public:
		bool operator()(const HyperChainInfo& left,const HyperChainInfo& right)
		{
			return left.meanLevel<right.meanLevel;
		}
	};
	
	double maxLevel=max_element(hyperChainInfos.begin(),hyperChainInfos.end(),Compare_Info())->meanLevel;

	class FindHyperChainInfos
	{
		double _level;
		vector<ChainAnalyzer::HyperChainInfo> _infos;
	public:
		FindHyperChainInfos(const double val):_level(val){}
		~FindHyperChainInfos(){}
		void operator()(const HyperChainInfo& info)
		{
			if(DoubleCompare(info.meanLevel,_level)==0)
			{
				_infos.push_back(info);
			}
		}
		vector<ChainAnalyzer::HyperChainInfo> GetResult()const {return _infos;}
	};

	FindHyperChainInfos findInfos(maxLevel);
	findInfos=for_each(hyperChainInfos.begin(),hyperChainInfos.end(),findInfos);

	return findInfos.GetResult();
}

vector<shared_ptr<Mind::ConceptChain>> ChainAnalyzer::GetHyperChains() const
{
	class InfoToChain
	{
	public:
		shared_ptr<ConceptChain> operator()(const HyperChainInfo& info)
		{
			return info.hyperChain;
		}
	};

	vector<shared_ptr<Mind::ConceptChain>> res(_hyperChainInfos.size());
	transform(_hyperChainInfos.begin(),_hyperChainInfos.end(),res.begin(),InfoToChain());

	return res;
}
