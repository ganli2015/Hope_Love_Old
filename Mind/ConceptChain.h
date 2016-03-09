#pragma once
#include "InOut.h"
#include "Concept.h"
#include <list>

namespace Mind
{
	class _MINDINOUT ConceptChain
	{
		typedef std::list<shared_ptr<Concept>> Sequence;

		Sequence _chain;
	public:
		ConceptChain(void);
		~ConceptChain(void);
		ConceptChain(const vector<shared_ptr<Concept>>& val);

		vector<shared_ptr<Concept>> GetConceptVec() const;
		void Push_Back(const shared_ptr<Concept> concept) {_chain.push_back(concept);}
		void Push_Front(const shared_ptr<Concept> concept) {_chain.push_front(concept);}
		shared_ptr<Concept> Front() const { return _chain.front();}
		shared_ptr<Concept> Back() const { return _chain.back();}
		bool Empty() const {return _chain.empty();}
		void Reverse() {reverse(_chain.begin(),_chain.end());}
		void Append(const shared_ptr<ConceptChain> chain);
		shared_ptr<ConceptChain> Copy() const;
		bool Same(const shared_ptr<ConceptChain> chain) const;
		bool Contain(const shared_ptr<Concept> concept) const;

		//判断<me>是否是parentChain的连续子序列。
		bool IsPartChainOf(const shared_ptr<ConceptChain> parentChain);
		bool IsSubSequenceOf(const shared_ptr<ConceptChain> parentChain) const;
	private:
		vector<int> ConceptChain::ComputePrefixFunction( const vector<shared_ptr<Concept>> P);
	};

	struct ConceptChainProperty
	{
		shared_ptr<ConceptChain> chain;
		double confidence;
	};
}


