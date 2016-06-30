#pragma once
#include "InOut.h"

namespace Mind
{
	class iConcept;

	//////////////////////////////////////////////////////////////////////////
	///iConceptChain contains a sequence of concepts.
	///It behaves like vector<shared_ptr<iConcept>>.
	//////////////////////////////////////////////////////////////////////////	
	class _MINDINTERFACEINOUT iConceptChain : public Obj<iConceptChain>
	{
	public:
		iConceptChain(void);
		virtual ~iConceptChain(void);

		virtual vector<shared_ptr<iConcept>> GetConceptVec() const =0;
		virtual void Push_Back(const shared_ptr<iConcept> concept)  =0;
		virtual void Push_Front(const shared_ptr<iConcept> concept)  =0;
		virtual shared_ptr<iConcept> Front() const =0 ;
		virtual shared_ptr<iConcept> Back() const =0 ;
		virtual bool Empty() const =0 ;
		virtual void Reverse() =0 ;
		virtual void Append(const shared_ptr<iConceptChain> chain) =0;
		virtual shared_ptr<iConceptChain> Copy() const =0;
		virtual bool Same(const shared_ptr<iConceptChain> chain) const =0;
		virtual bool Contain(const shared_ptr<iConcept> concept) const =0;
		virtual unsigned int Size() const =0;

		//////////////////////////////////////////////////////////////////////////
		///Check whether <me> is a Continuous sub sequence of <parentChain>.
		//////////////////////////////////////////////////////////////////////////
		virtual bool IsPartChainOf(const shared_ptr<iConceptChain> parentChain) const =0;
		
		//////////////////////////////////////////////////////////////////////////
		///Check whether <me> is a sub sequence (not necessary continuous) of <parentChain>.
		//////////////////////////////////////////////////////////////////////////
		virtual bool IsSubSequenceOf(const shared_ptr<iConceptChain> parentChain) const =0;
	};

	struct ConceptChainProperty
	{
		shared_ptr<iConceptChain> chain;
		double confidence;
	};
}


