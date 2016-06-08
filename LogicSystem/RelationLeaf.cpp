#include "StdAfx.h"
#include "RelationLeaf.h"
#include "Symbol.h"

#include "../MindInterface/iSymbol.h"
#include "../MindInterface/iExpression.h"
#include "../MindInterface/iConceptInteractTable.h"
#include "../MindInterface/iConcept.h"
#include "../MindInterface/iRelationConstraint.h"

#include "../MindInterface/iMindElementCreator.h"

#include "../Mathmatic/FindSequence.h"

using namespace Mind;
namespace LogicSystem
{
	RelationLeaf::RelationLeaf(void):_connectTag("->"),_sepTag(',')
	{
	}


	RelationLeaf::~RelationLeaf(void)
	{
	}

	void RelationLeaf::AddRelation( const shared_ptr<ConSymbol> from,const shared_ptr<ConSymbol> to )
	{
		assert(from!=NULL && to!=NULL);
		_relations.push_back(SymbolPair(from,to));
	}

	void RelationLeaf::AddConstraint( const shared_ptr<iRelationConstraint> constraint )
	{
		assert(constraint!=NULL);
		_constraints.push_back(constraint);
	}

	std::string RelationLeaf::GetString() const
	{
		string res="";
		for (unsigned int i=0;i<_relations.size();++i)
		{
			res+=_relations[i].First()->GetString();
			res+=_connectTag;
			res+=_relations[i].Second()->GetString();
			
			if(i!=_relations.size()-1)
			{
				res+=_sepTag;
			}
		}

		return res;
	}

	bool RelationLeaf::Satisfy( const shared_ptr<iExpression> expre ,const bool exact)
	{
		shared_ptr<iConceptInteractTable> interTable=expre->GetProtoInteractTable();
		
		if(exact && _relations.size()!=interTable->GetAllRelations().size())
		{
			return false;
		}
		else
			return InterTableSatisfyRelation(interTable);
	}

	bool RelationLeaf::Satisfy( const shared_ptr<Mind::iConceptInteractTable> conceptTable ,const bool exact)
	{
		if(exact && _relations.size()!=conceptTable->GetAllRelations().size())
		{
			return false;
		}
		else
			return InterTableSatisfyRelation(conceptTable);
	}

	bool RelationLeaf::InterTableSatisfyRelation( const shared_ptr<iConceptInteractTable> interTable)
	{
		vector<ConceptPair> conPairs=interTable->GetAllRelations();
		vector<vector<PairInfo>> matchedPairSeq=FindMatchedPairSequence(conPairs);
		if(matchedPairSeq.empty() )
		{
			_satisfiedSequence.clear();

			return false;
		}
		else
		{
			_satisfiedSequence=matchedPairSeq.front();

			return true;
		}

// 		for (unsigned int i=0;i<matchedPairSeq.size();++i)
// 		{
// 			if(SatifyConstraint(matchedPairSeq[i],_constraints))//Any of them satisfies ,then we consider <expre> satisfying.
// 			{
// 				_satisfiedSequence=matchedPairSeq[i];
// 
// 				return true;
// 			}
// 		}
// 
// 		_satisfiedSequence.clear();
// 
// 		return false;
	}

	vector<iRelation::PairSequence> RelationLeaf::FindMatchedPairSequence(const vector<ConceptPair>& conceptPairs) const
	{
		//vector<vector<PairInfo>> matchedPairSeq=FindMatchedPairSequence(_relations,conceptPairs);

		vector<vector<PairInfo>> matchedPairSeq;
		Recursive_FindMatchedPairSequence(_relations,conceptPairs,matchedPairSeq);
		RemoveSequencesUnsatifyConstraints(_constraints,matchedPairSeq);

		return matchedPairSeq;
	}

	vector<RelationLeaf::ConceptPair> RelationLeaf::FindMatchedPairs(const SymbolPair& symbolPair,const vector<ConceptPair>& cPairs)
	{
		class FindConceptPair
		{
			SymbolPair _symbolPair;
			vector<ConceptPair> _result;

		public:
			FindConceptPair(const SymbolPair& val):_symbolPair(val){}
			~FindConceptPair(){}
			
			vector<ConceptPair> GetResult() const {return _result;}
			void operator()(const ConceptPair& cPair)
			{
				if(_symbolPair.First()->Match(cPair.first) && _symbolPair.Second()->Match(cPair.second))
				{
					_result.push_back(cPair);
				}
			}
		};

		FindConceptPair findPairs(symbolPair);
		findPairs=for_each(cPairs.begin(),cPairs.end(),findPairs);
		vector<RelationLeaf::ConceptPair> res=findPairs.GetResult();

		return res;
	}

	vector<vector<RelationLeaf::PairInfo>> RelationLeaf::FindMatchedPairSequence(const vector<SymbolPair>& sPairs,const vector<ConceptPair>& cPairs)
	{
		class FindEachRelatedConceptPairs
		{
			vector<ConceptPair> _cPairs;

		public:
			FindEachRelatedConceptPairs(const vector<ConceptPair>& cPairs):_cPairs(cPairs){}
			~FindEachRelatedConceptPairs(){}

			vector<PairInfo> operator()(const SymbolPair& sPair)
			{
				vector<PairInfo> res;
				vector<ConceptPair> relatedPairs= FindMatchedPairs(sPair,_cPairs);
				res.reserve(relatedPairs.size());
				for (unsigned int i=0;i<relatedPairs.size();++i)
				{
					PairInfo info;
					info.cPair=relatedPairs[i];
					info.sPair=sPair;
					res.push_back(info);
				}

				return res;
			}
		};

		//Each element in <relatedPairs> is all the concept pairs that one symbol pair is related with.
		vector<vector<PairInfo>> relatedPairs;
		transform(sPairs.begin(),sPairs.end(),back_inserter(relatedPairs),FindEachRelatedConceptPairs(cPairs));

		//Each element in <pairSequence> is concept pairs that all different symbol pairs are related with.
		vector<vector<PairInfo>> pairSequence=Math::GetAllCombinations<PairInfo>::Get(relatedPairs);

		return pairSequence;
	}

	void RelationLeaf::Recursive_FindMatchedPairSequence(const vector<SymbolPair>& sPairs,const vector<ConceptPair>& cPairs,
		vector<PairSequence>& sequence) const
	{
		if(sPairs.empty())
		{
			return;
		}

		SymbolPair curSymbolPair=sPairs.front();
		vector<SymbolPair> remainingSymbolPairs(sPairs.begin()+1,sPairs.end());

		//Go through <cPairs>.
		//for each matched cPair, delete it from <cPairs> and delete the matched symbol from <sPairs>.
		//Then search for the remaining <cPairs> and <sPairs>.
		for (unsigned int i=0;i<cPairs.size();++i)
		{
			if(!(curSymbolPair.First()->Match(cPairs[i].first) && curSymbolPair.Second()->Match(cPairs[i].second))) continue;//Not matched
			
			//Generate concept pairs without the current matched one.
			vector<ConceptPair> remainingCPairs(cPairs);
			remainingCPairs.erase(remainingCPairs.begin()+i);

			if(remainingSymbolPairs.empty())//Currently reach the end of the sPairs, then construct the last PairInfo.
			{
				PairSequence seq=CreateSequenceWithOneElem(curSymbolPair,cPairs[i]);
				sequence.push_back(seq);
			}
			else
			{
				vector<PairSequence> subSequence;
				Recursive_FindMatchedPairSequence(remainingSymbolPairs,remainingCPairs,subSequence);
				//Merge each subSequence with current sequence. 
				for (unsigned int j=0;j<subSequence.size();++j)
				{
					PairSequence seq=CreateSequenceWithOneElem(curSymbolPair,cPairs[i]);
					seq.insert(seq.end(),subSequence[j].begin(),subSequence[j].end());
					sequence.push_back(seq);
				}
			}
			
		}
	}

	RelationLeaf::PairSequence RelationLeaf::CreateSequenceWithOneElem(const SymbolPair& sPair,const ConceptPair& cPair) const
	{
		PairSequence seq;
		PairInfo info;
		info.cPair=cPair;
		info.sPair=sPair;
		seq.push_back(info);

		return seq;
	}

	shared_ptr<iRelation> RelationLeaf::GenerateSpecialRelation() const
	{
		shared_ptr<RelationLeaf> res(new RelationLeaf());

		for (unsigned int i=0;i<_relations.size();++i)
		{
			shared_ptr<iConcept> firstObj=_relations[i].First()->GetReferredObject();
			shared_ptr<iConcept> secondObj=_relations[i].Second()->GetReferredObject();
			if(firstObj==NULL || secondObj==NULL)
			{
				return NULL;
			}
			else
			{
				shared_ptr<ConSymbol> fromSymbol(new Symbol<iConcept>(firstObj));
				shared_ptr<ConSymbol> toSymbol(new Symbol<iConcept>(secondObj));
				res->AddRelation(fromSymbol,toSymbol);
			}
		}

		return res;
	}

	shared_ptr<Mind::iConceptInteractTable> RelationLeaf::GenerateConceptTable() const
	{
		shared_ptr<iConceptInteractTable> res=iMindElementCreator::CreateConceptInteractTable();

		for (unsigned int i=0;i<_relations.size();++i)
		{
			shared_ptr<iConcept> firstObj=_relations[i].First()->GetReferredObject();
			shared_ptr<iConcept> secondObj=_relations[i].Second()->GetReferredObject();
			if(firstObj==NULL || secondObj==NULL)
			{
				continue;
			}
			else
			{
				res->Add(firstObj,secondObj);
			}
		}

		return res;
	}

}

