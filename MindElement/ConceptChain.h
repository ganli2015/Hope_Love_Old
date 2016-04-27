#pragma once
#include "InOut.h"
#include <list>
#include "../MindInterface/iConceptChain.h"

namespace Mind
{
	class iConcept;

	class _MINDELEMENTINOUT ConceptChain : public iConceptChain
	{
		typedef std::vector<shared_ptr<iConcept>> Sequence;

		list<shared_ptr<iConcept>> _chain;
	public:
		ConceptChain(void);
		~ConceptChain(void);
		ConceptChain(const vector<shared_ptr<iConcept>>& val);

		virtual vector<shared_ptr<iConcept>> GetConceptVec() const;
		virtual void Push_Back(const shared_ptr<iConcept> concept) {_chain.push_back(concept);}
		virtual void Push_Front(const shared_ptr<iConcept> concept) {_chain.push_front(concept);}
		virtual shared_ptr<iConcept> Front() const { return _chain.front();}
		virtual shared_ptr<iConcept> Back() const { return _chain.back();}
		virtual bool Empty() const {return _chain.empty();}
		virtual void Reverse() {reverse(_chain.begin(),_chain.end());}
		virtual void Append(const shared_ptr<iConceptChain> chain);
		virtual shared_ptr<iConceptChain> Copy() const;
		virtual bool Same(const shared_ptr<iConceptChain> chain) const;
		virtual bool Contain(const shared_ptr<iConcept> concept) const;

		//判断<me>是否是parentChain的连续子序列。
		virtual bool IsPartChainOf(const shared_ptr<iConceptChain> parentChain) const ;
		virtual bool IsSubSequenceOf(const shared_ptr<iConceptChain> parentChain) const;
	private:
		vector<int> ConceptChain::ComputePrefixFunction( const vector<shared_ptr<iConcept>> P) const;
	};

	
}


