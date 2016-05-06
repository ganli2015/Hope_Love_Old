#pragma once
#include "InOut.h"

namespace DataCollection
{
	class GrammarPattern;
	enum PartOfSpeech;
}

namespace Mind
{
	struct Identity
	{
		string str;
		//表示同一个string所对应的不同的concept。引导词的id等于-1！
		//目前同一个单词的同一个词性只对应于一个id！
		//也就是说这个id暂时起不到作用！
		int id;
	};

	class iConcept;
	class iConceptInteractTable;
	class iConceptChain;
	namespace CommonFunction
	{
		//把<from>和<to>的所有相互作用都添加到table
		void _MINDINTERFACEINOUT AppendToInteractTable(const vector<shared_ptr<iConcept>>& from,const vector<shared_ptr<iConcept>>& to,shared_ptr<iConceptInteractTable> table);

		//如果没有找到，则返回-1.
		int _MINDINTERFACEINOUT IndexOf(const vector<shared_ptr<iConcept>>& concepts,const shared_ptr<iConcept> concept);

		bool _MINDINTERFACEINOUT IsSameConcept(const shared_ptr<iConcept> left,const shared_ptr<iConcept> right);

		void _MINDINTERFACEINOUT WriteConcepts(const vector<shared_ptr<iConcept>>& vec,ofstream& out);

		void _MINDINTERFACEINOUT RemoveSameChain( vector<shared_ptr<iConceptChain>>& chains ) ;

		double _MINDINTERFACEINOUT ComputeP_GrammarLocalAnalysis(const DataCollection::GrammarPattern& pattern);

		//计算<curPos>的置信度，假设其相邻两个词性是<forwardPos>和<backwardPos>.
		double _MINDINTERFACEINOUT ComputeP_GrammarLocal(const DataCollection::PartOfSpeech& curPos,const DataCollection::PartOfSpeech& forwardPos,const DataCollection::PartOfSpeech& backwardPos);

		void _MINDINTERFACEINOUT OutputConceptPairs(const vector<MindType::ConceptPair>& pairs,ostream& out);

		class _MINDINTERFACEINOUT SameConcept
		{
			shared_ptr<iConcept> _me;
		public:
			SameConcept(const shared_ptr<iConcept> val):_me(val){}
			~SameConcept(){}

			bool operator()(const shared_ptr<iConcept> val);
		};
	}
}

