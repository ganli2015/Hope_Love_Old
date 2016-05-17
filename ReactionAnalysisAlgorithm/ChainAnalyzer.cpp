#include "StdAfx.h"
#include "ChainAnalyzer.h"
#include "ExtractConceptChains.h"

#include "../Mathmatic/MathTool.h"
#include "../Mathmatic/FindSequence.h"

#include "../MindInterface/iCerebrum.h"
#include "../MindInterface/iConcept.h"
#include "../MindInterface/iConceptChain.h"
#include "../MindInterface/iConceptInteractTable.h"
#include "../MindInterface/iConceptLevelTable.h"

#include "../MindElement/ConceptChain.h"
#include "../Mind/CommonFunction.h"

using namespace Mind;
using namespace Math;

ChainAnalyzer::ChainAnalyzer(void):_brain(iCerebrum::Instance())
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
		vector<shared_ptr<iConceptChain>> hyperChains;
		ComputeHyperChains(property.chain,hyperChains);
		if(hyperChains.empty()) continue;

		vector<double> levels;
		ComputeHyperChainLevels(hyperChains,baseChains[i].chain,levels);
		vector<HyperChainInfo> hyperInfos=AssembleHyperChainInfo(hyperChains,levels,property.confidence);


#ifdef _COUT_DEBUG_INFO
		OutputHyperChains(hyperInfos,baseChains[i].chain,out);
#endif // _DEBUG

		vector<HyperChainInfo> selectedHyperInfos=SelectHyperChainsOfMaxLevels(hyperInfos);

		_hyperChainInfos.insert(_hyperChainInfos.end(),selectedHyperInfos.begin(),selectedHyperInfos.end());
	}


}

void ChainAnalyzer::ComputeHyperChains( const shared_ptr<iConceptChain> baseChain,vector<shared_ptr<iConceptChain>>& hyperChains )
{
	vector<shared_ptr<iConcept>> conceptSequence=baseChain->GetConceptVec();

	vector<vector<shared_ptr<iConcept>>> backwardConceptSequence;//存放所有backward concept的容器，第i个元素表示conceptSequence的第i个concept的所有backward concept。
	backwardConceptSequence.reserve(conceptSequence.size());
	for (unsigned int i=0;i<conceptSequence.size();++i)
	{
		vector<shared_ptr<iConcept>> backConcepts=_brain->SearchBackwardConcepts(conceptSequence[i]);
		backConcepts.push_back(conceptSequence[i]);
		backwardConceptSequence.push_back(backConcepts);
	}

	//所有backward concept的可能组合序列
	vector<vector<shared_ptr<iConcept>>> combinations=Math::GetAllCombinations<shared_ptr<iConcept>>::Get(backwardConceptSequence);
	for (unsigned int i=0;i<combinations.size();++i)
	{
		vector<shared_ptr<iConceptChain>> properCombi=ComputeProperCombination(combinations[i],baseChain);
		hyperChains.insert(hyperChains.end(),properCombi.begin(),properCombi.end());
	}
}

vector<shared_ptr<iConceptChain>> ChainAnalyzer::ComputeProperCombination( const vector<shared_ptr<Mind::iConcept>>& combination,const shared_ptr<Mind::iConceptChain> baseChain ) const
{
	vector<shared_ptr<iConceptChain>> res;

	vector<vector<shared_ptr<iConcept>>> subSequences=GetAllSubSequence<shared_ptr<iConcept>>::Get(combination);
	for (unsigned int i=0;i<subSequences.size();++i)
	{
		if(CoverBase(subSequences[i],baseChain))
		{
			res.push_back(shared_ptr<iConceptChain>(new ConceptChain(subSequences[i])));
		}
	}

	return res;
}

bool ChainAnalyzer::CoverBase(const vector<shared_ptr<iConcept>>& hyperChain,const shared_ptr<iConceptChain>& baseChain) const
{
	typedef pair<shared_ptr<Mind::iConcept>,shared_ptr<Mind::iConcept>> ConceptPair;

	//计算两两Concept之间的相互作用，得到所有相互作用对。
	vector<ConceptPair> allPairs;
	for (unsigned int i=0;i<hyperChain.size()-1;++i)
	{
		shared_ptr<iConceptInteractTable> interactTable=hyperChain[i]->DeepInteractWith(hyperChain[i+1]);
		vector<ConceptPair> basePairs=interactTable->GetAllRelations();
		allPairs.insert(allPairs.end(),basePairs.begin(),basePairs.end());
	}

	//对allPairs提取所有的Concept Chain。
	vector<shared_ptr<iConceptChain>> chains;
	try
	{
		chains=ExtractConceptChains::Extract(allPairs);
	}
	catch(...)
	{
		throw;
	}
	for (unsigned int i=0;i<chains.size();++i)
	{
		if(baseChain->IsSubSequenceOf(chains[i]))
		{
			return true;
		}
	}
	return false;
}

int ChainAnalyzer::OverlappedCount( const int startIndex,const vector<shared_ptr<iConcept>>& checkChain,const vector<shared_ptr<iConcept>>& testChain ) const
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

void ChainAnalyzer::OutputHyperChains( const vector<HyperChainInfo>& hyperChainInfos,const shared_ptr<Mind::iConceptChain> baseChain,ofstream& out )
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

void ChainAnalyzer::ComputeHyperChainLevels( const vector<shared_ptr<iConceptChain>>& hyperChains,const shared_ptr<Mind::iConceptChain> baseChain,vector<double>& levels ) const
{
	class ComputeLevel
	{
		shared_ptr<Mind::iConceptChain> _baseChain;
	public:
		ComputeLevel(const shared_ptr<Mind::iConceptChain> val):_baseChain(val){}
		~ComputeLevel(){}
		double operator()(const shared_ptr<Mind::iConceptChain> hyperChain)
		{
			return ChainAnalyzer::ComputeHyperChainMeanLevel(hyperChain,_baseChain);
		}
	};

	levels.clear();
	levels.reserve(hyperChains.size());
	transform(hyperChains.begin(),hyperChains.end(),back_inserter(levels),ComputeLevel(baseChain));
}

double ChainAnalyzer::ComputeHyperChainMeanLevel( const shared_ptr<Mind::iConceptChain> hyperChain,const shared_ptr<Mind::iConceptChain> baseChain )
{
	vector<shared_ptr<iConcept>> hyperConcepts=hyperChain->GetConceptVec();
	vector<shared_ptr<iConcept>> baseConcepts=baseChain->GetConceptVec();
	vector<int> levels;
	for (unsigned int i=0;i<hyperConcepts.size();++i)
	{
		shared_ptr<iConceptLevelTable> levelTable=hyperConcepts[i]->GetLevelTable();
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

vector<ChainAnalyzer::HyperChainInfo> ChainAnalyzer::AssembleHyperChainInfo( const vector<shared_ptr<Mind::iConceptChain>>& hyperChains, const vector<double>& levels, const double confidence )
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

vector<shared_ptr<Mind::iConceptChain>> ChainAnalyzer::GetHyperChains() const
{
	class InfoToChain
	{
	public:
		shared_ptr<iConceptChain> operator()(const HyperChainInfo& info)
		{
			return info.hyperChain;
		}
	};

	vector<shared_ptr<Mind::iConceptChain>> res(_hyperChainInfos.size());
	transform(_hyperChainInfos.begin(),_hyperChainInfos.end(),res.begin(),InfoToChain());

	return res;
}
