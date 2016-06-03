#pragma once
#include "InOut.h"
#include "../MindInterface/iLogic.h"

namespace Mind
{
	class iCerebrum;
	struct DescMatchedConceptInfo;
};

namespace LogicSystem
{
	class _LOGICSYSTEMINOUT Logic : public iLogic
	{
		typedef MindType::ConceptPair ConceptPair;

		friend class Test_LogicSystem;
	public:
		Logic(void);
		~Logic(void);

		virtual LogicResult Determine(const shared_ptr<iExpression> condition,const shared_ptr<iExpression> conclusion) const;

		virtual vector<shared_ptr<iDeduceResult>> Deduce(const shared_ptr<iExpression> condition)  const;

		virtual vector<shared_ptr<iDeduceResult>> FinalDeduce(const shared_ptr<iExpression> condition)  const;

		virtual vector<shared_ptr<iReduceResult>> Reduce(const shared_ptr<Mind::iConceptInteractTable> conceptTable) const ;


	private:
		///Filter <total> with <partial> and return the remaining.
		vector<Logic::ConceptPair> FilterPartialConceptPairs(const vector<ConceptPair>& total, const vector<ConceptPair>& partial) const;
		///Find a ConceptPair whose first concept is <concept>.
		bool FindPair_SameFirstConcept(const vector<ConceptPair>& total,const shared_ptr<Mind::iConcept> concept,Logic::ConceptPair& resultPair) const;
		///Find a ConceptPair whose second concept is <concept>.
		bool FindPair_SameSecondConcept(const vector<ConceptPair>& total,const shared_ptr<Mind::iConcept> concept,Logic::ConceptPair& resultPair) const;
	
		vector<shared_ptr<iReduceResult>> ReduceConceptPairSequence(const vector<ConceptPair>& subPairs,const vector<ConceptPair>& totalPairs,const Mind::iCerebrum* brain) const;
		shared_ptr<iReduceResult> ReduceFromMatchedConcept(const Mind::DescMatchedConceptInfo& matchedConceptInfo, const vector<ConceptPair>& subPairs,const vector<ConceptPair>& remainingPairs) const;
	};
}


