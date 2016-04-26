#pragma once
#include "InOut.h"
#include <list>

namespace Mind
{
	class iConcept;

	class _MINDELEMENTINOUT ConceptChain
	{
		typedef std::list<shared_ptr<iConcept>> Sequence;

		Sequence _chain;
	public:
		ConceptChain(void);
		~ConceptChain(void);
		ConceptChain(const vector<shared_ptr<iConcept>>& val);

		vector<shared_ptr<iConcept>> GetConceptVec() const;
		void Push_Back(const shared_ptr<iConcept> concept) {_chain.push_back(concept);}
		void Push_Front(const shared_ptr<iConcept> concept) {_chain.push_front(concept);}
		shared_ptr<iConcept> Front() const { return _chain.front();}
		shared_ptr<iConcept> Back() const { return _chain.back();}
		bool Empty() const {return _chain.empty();}
		void Reverse() {reverse(_chain.begin(),_chain.end());}
		void Append(const shared_ptr<ConceptChain> chain);
		shared_ptr<ConceptChain> Copy() const;
		bool Same(const shared_ptr<ConceptChain> chain) const;
		bool Contain(const shared_ptr<iConcept> concept) const;

		//判断<me>是否是parentChain的连续子序列。
		bool IsPartChainOf(const shared_ptr<ConceptChain> parentChain);
		bool IsSubSequenceOf(const shared_ptr<ConceptChain> parentChain) const;
	private:
		vector<int> ConceptChain::ComputePrefixFunction( const vector<shared_ptr<iConcept>> P);
	};

	struct ConceptChainProperty
	{
		shared_ptr<ConceptChain> chain;
		double confidence;
	};
}


