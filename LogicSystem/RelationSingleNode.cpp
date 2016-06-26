#include "stdafx.h"
#include "RelationSingleNode.h"
#include "Symbol.h"

#include "../MindInterface/iSymbol.h"
#include "../MindInterface/iExpression.h"
#include "../MindInterface/iConcept.h"

using namespace Mind;

namespace LogicSystem
{
	RelationSingleNode::RelationSingleNode()
	{
	}


	RelationSingleNode::~RelationSingleNode()
	{
	}

	std::string RelationSingleNode::GetString() const
	{
		return _symbol->GetString();
	}

	bool RelationSingleNode::Satisfy(const shared_ptr<iExpression> expre, const bool exact /*= true*/)
	{
		//Only if there is only one concept in <expre> and the concept matches <_symbol>, then satisfy.
		shared_ptr<iConcept> singleConcept = expre->GetProtoConcept();
		if (singleConcept != NULL && _symbol->Match(singleConcept))
		{
			//Add connection between <_symbol> and <singleConcept> to PairInfo <_satisfiedSequence>.
			//As there is only one concept instead of pair, I designate both 'from' symbol and 'to' symbol as <_symbol> for convenience.

			SymbolPair sPair(_symbol, _symbol);
			ConceptPair cPair = make_pair(singleConcept, singleConcept);
			PairInfo pairInfo;
			pairInfo.cPair = cPair;
			pairInfo.sPair = sPair;
			_satisfiedSequence.push_back(pairInfo);

			return true;
		}
		else
		{
			return false;
		}
	}

	bool RelationSingleNode::Satisfy(const shared_ptr<Mind::iConceptInteractTable> expre, const bool exact /*= true*/)
	{
		return false;
	}

	std::vector<LogicSystem::iRelation::PairSequence> RelationSingleNode::FindMatchedPairSequence(const vector<ConceptPair>& conceptPairs) const
	{
		return vector<LogicSystem::iRelation::PairSequence>();
	}

	shared_ptr<LogicSystem::iRelation> RelationSingleNode::GenerateSpecialRelation() const
	{
		//Check whether <_symbol> binds to something.
		//If not , fail to generate Special relation.
		shared_ptr<iConcept> singleConcept = _symbol->GetReferredObject();
		if (singleConcept == NULL)
		{
			return NULL;
		}

		//Add a new created symbol binding to the concept of <me>.
		//Not use a ref to current symbol as it may change.
		shared_ptr<RelationSingleNode> res(new RelationSingleNode());
		shared_ptr<ConSymbol> newSymbol(new Symbol<iConcept>(singleConcept));
		res->SetSymbol(newSymbol);

		return res;
	}

	shared_ptr<Mind::iConceptInteractTable> RelationSingleNode::GenerateConceptTable() const
	{
		return NULL;
	}

	shared_ptr<Mind::iConcept> RelationSingleNode::GenerateSingleConcept() const
	{
		shared_ptr<iConcept> singleConcept = _symbol->GetReferredObject();

		return singleConcept;
	}

}

