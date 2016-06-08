#pragma once
#include "InOut.h"
#include "DeduceResult.h"
#include "../MindInterface/iLogic.h"
#include <list>

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
		typedef list<shared_ptr<Mind::iConceptInteractTable>> TableList;
		typedef TableList::iterator TableIter;
		typedef TableList::const_iterator TableIterConst;
		typedef list<shared_ptr<Mind::iConcept>> ConceptList;

		friend class Test_LogicSystem;
	public:
		Logic(void);
		~Logic(void);

		virtual LogicResult Determine(const shared_ptr<iExpression> condition,const shared_ptr<iExpression> conclusion) const;

		virtual vector<shared_ptr<iDeduceResult>> Deduce(const shared_ptr<iExpression> condition)  const;

		virtual vector<shared_ptr<iDeduceResult>> FinalDeduce(const shared_ptr<iExpression> condition)  const;

		virtual vector<shared_ptr<iReduceResult>> Reduce(const shared_ptr<Mind::iConceptInteractTable> conceptTable) const ;


	private:
		vector<shared_ptr<iDeduceResult>> Deduce(const shared_ptr<Mind::iConceptInteractTable> condition)  const;

		vector<Logic::ConceptPair> FilterPartialConceptPairs( const vector<ConceptPair>& total, const vector<ConceptPair>& partial ) const;
		///Find a ConceptPair whose first concept is <concept>.
		bool FindPair_SameFirstConcept(const vector<ConceptPair>& total,const shared_ptr<Mind::iConcept> concept,Logic::ConceptPair& resultPair) const;
		///Find a ConceptPair whose second concept is <concept>.
		bool FindPair_SameSecondConcept(const vector<ConceptPair>& total,const shared_ptr<Mind::iConcept> concept,Logic::ConceptPair& resultPair) const;
	
		vector<shared_ptr<iReduceResult>> ReduceConceptPairSequence(const vector<ConceptPair>& subPairs,const vector<ConceptPair>& totalPairs,const Mind::iCerebrum* brain) const;
		shared_ptr<iReduceResult> ReduceFromMatchedConcept(const Mind::DescMatchedConceptInfo& matchedConceptInfo, const vector<ConceptPair>& subPairs,const vector<ConceptPair>& remainingPairs) const;
	
	
		list<shared_ptr<Mind::iConceptInteractTable>> ToConceptTable(const vector<shared_ptr<iDeduceResult>>& deduceResults) const;
		list<shared_ptr<Mind::iConceptInteractTable>> ToConceptTable(const vector<shared_ptr<iReduceResult>>& reduceResults) const;
		list<shared_ptr<Mind::iConcept>> ToConceptList(const vector<shared_ptr<iReduceResult>>& reduceResults) const;
		void ReduceTableList(const TableList& tableList,
			TableList& reducedTables,TableList& noChangedTables,ConceptList& conceptResults) const;
		void DeduceTableList(const TableList& reducedTables,TableList& noChangedTables,
			TableList& tableForIter) const;
		vector<shared_ptr<iDeduceResult>> AssembleDeduceResults(const ConceptList& conceptResults,
			const TableList& finalDeduceTables) const;

	private:
		template<class InputType>
		class ToDeduceResult
		{
		public:
			shared_ptr<iDeduceResult> operator()(const shared_ptr<InputType> input)
			{
				return shared_ptr<iDeduceResult>(new DeduceResult<InputType>(input));
			}
		};
	};
}


