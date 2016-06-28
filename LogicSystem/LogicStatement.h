#pragma once
#include "InOut.h"
#include "../MindInterface/iLogicStatement.h"

namespace LogicSystem
{
	
	class _LOGICSYSTEMINOUT LogicStatement : public iLogicStatement
	{
		pair<shared_ptr<iRelation>,shared_ptr<iRelation>> _relationPair;

	public:
		LogicStatement(const shared_ptr<iRelation> condition,const shared_ptr<iRelation> result);
		~LogicStatement(void);

		virtual shared_ptr<iDeduceResult> Deduce(const shared_ptr<iExpression> condition) const ;
		virtual shared_ptr<iDeduceResult> Deduce(const shared_ptr<Mind::iConceptInteractTable> condition) const;

	private:
		//////////////////////////////////////////////////////////////////////////
		///Generate deduction result from <resultRelation>.
		///Only when <resultRelation> can be transformed to a concept table , will there be a non-null iDeduceResult.
		///Then remaining concept pairs <remainPairs> append to iDeduceResult.
		//////////////////////////////////////////////////////////////////////////
		shared_ptr<iDeduceResult> GenerateConceptTableResult(const shared_ptr<iRelation> resultRelation, const vector<MindType::ConceptPair>& remainPairs) const;

		//////////////////////////////////////////////////////////////////////////
		///Generate a deduction result when there is a single concept in <resultRelation>.
		///But the returned iDeduceResult not necessarily contains a single concept and also may contain concept tables.
		///In the latter situation, the single concept is transformed to a concept pair 
		///which as well as <remainPairs> are included in  <iDeduceResult>, thus information of remaining part is retained.
		//////////////////////////////////////////////////////////////////////////
		shared_ptr<iDeduceResult> GenerateSingleConceptResult(const shared_ptr<iRelation> resultRelation, const vector<MindType::ConceptPair>& subPairs, const vector<MindType::ConceptPair>& remainPairs) const;
		
		//////////////////////////////////////////////////////////////////////////
		///Transform <concept> to <newConceptPair> according to connection between <subPairs> and <remainPairs>.
		//////////////////////////////////////////////////////////////////////////
		bool TransformConceptToConceptPair(const shared_ptr<Mind::iConcept> concept, const vector<MindType::ConceptPair>& subPairs, const vector<MindType::ConceptPair>& remainPairs, MindType::ConceptPair& newConceptPair) const;
		
		//////////////////////////////////////////////////////////////////////////
		///Check whether the second concept of <pair> is the same with one of the first concept among <remainPairs>.
		//////////////////////////////////////////////////////////////////////////
		static bool HasForwardConnection(const MindType::ConceptPair& pair, const vector<MindType::ConceptPair>& remainPairs);
		//////////////////////////////////////////////////////////////////////////
		///Check whether the first concept of <pair> is the same with one of the second concept among <remainPairs>.
		//////////////////////////////////////////////////////////////////////////
		static bool HasBackwardConnection(const MindType::ConceptPair& pair, const vector<MindType::ConceptPair>& remainPairs);

		static shared_ptr<iDeduceResult> GenerateResult(const shared_ptr<iRelation> conditionRelation, const shared_ptr<iRelation> resultRelation);
	};
}


