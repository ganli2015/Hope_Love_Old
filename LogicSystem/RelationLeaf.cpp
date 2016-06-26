#include "StdAfx.h"
#include "RelationLeaf.h"
#include "Symbol.h"
#include "Number.h"

#include "../MindInterface/iSymbol.h"
#include "../MindInterface/iExpression.h"
#include "../MindInterface/iConceptInteractTable.h"
#include "../MindInterface/iConcept.h"
#include "../MindInterface/iRelationConstraint.h"

#include "../MindInterface/iMindElementCreator.h"

#include "../Mathmatic/FindSequence.h"

#include "../CommonTools/GeneralFunctor.h"


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

	void RelationLeaf::AddRelation( const shared_ptr<ConSymbol> from,const shared_ptr<ConSymbol> to, const shared_ptr<Num> num )
	{
		_relations.push_back(SymbolPair(from,to,num));
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
		
		//If <expre> should exactly satisfy the relations,
		//The number of symbol pairs must equal to concept pairs in <interTable>.
		if(exact && _relations.size()!=interTable->GetPairCount())
		{
			return false;
		}
		else
			return InterTableSatisfyRelation(interTable);
	}

	bool RelationLeaf::Satisfy( const shared_ptr<Mind::iConceptInteractTable> conceptTable ,const bool exact)
	{
		//If <expre> should exactly satisfy the relations,
		//The number of symbol pairs must equal to concept pairs in <conceptTable>.
		if(exact && _relations.size()!=conceptTable->GetPairCount())
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
	}

	vector<iRelation::PairSequence> RelationLeaf::FindMatchedPairSequence(const vector<ConceptPair>& conceptPairs) const
	{
		//vector<vector<PairInfo>> matchedPairSeq=FindMatchedPairSequence(_relations,conceptPairs);

		vector<vector<PairInfo>> matchedPairSeq;
		Recursive_FindMatchedPairSequence(_relations,conceptPairs,matchedPairSeq);
		RemoveSequencesUnsatifyConstraints(_constraints,matchedPairSeq);

		return matchedPairSeq;
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
			if(!ConPairSymPairMatch(cPairs[i], curSymbolPair)) continue;//Not matched
			
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

	bool RelationLeaf::ConPairSymPairMatch(const ConceptPair& cPair, const SymbolPair& sPair) const
	{
		CREATE_FUNCTOR_IR(BaseMatchSymbol,shared_ptr<ConSymbol>,shared_ptr<iConcept>,bool,
			if(_init->Match(input))
			{
				return true;
			}
			else
			{
				return false;
			}
		);

		vector<shared_ptr<iConcept>> fromBase = cPair.first->GetBase();
		vector<shared_ptr<iConcept>>::iterator fromMatchIter = find_if(fromBase.begin(), fromBase.end(), BaseMatchSymbol(sPair.First()));
		if(fromMatchIter==fromBase.end())
		{
			return false;
		}

		vector<shared_ptr<iConcept>> toBase = cPair.second->GetBase();
		vector<shared_ptr<iConcept>>::iterator toMatchIter = find_if(toBase.begin(), toBase.end(), BaseMatchSymbol(sPair.Second()));
		if (toMatchIter == toBase.end())
		{
			return false;
		}

		return true;
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
			//Generate a symbol pair or symbol pairs according to the repetition number.
			//After using method <Satisfy>, each symbol has binded to a concrete concept.

			vector<SymbolPair> specialSymbolPairs=GeneratePairSequence(_relations[i]);
			if(specialSymbolPairs.empty())
			{
				return NULL;
			}

			for (unsigned int j=0;j<specialSymbolPairs.size();++j)
			{
				res->AddRelation(specialSymbolPairs[j].First(),specialSymbolPairs[j].Second());
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

	vector<RelationLeaf::SymbolPair> RelationLeaf::GeneratePairSequence( const SymbolPair& symbolPair ) const
	{
		vector<SymbolPair> res;

		shared_ptr<iConcept> firstObj=symbolPair.First()->GetReferredObject();
		shared_ptr<iConcept> secondObj=symbolPair.Second()->GetReferredObject();

		if(firstObj==NULL || secondObj==NULL)
		{
			return res;
		}

		shared_ptr<ConSymbol> fromSymbol(new Symbol<iConcept>(firstObj));
		shared_ptr<ConSymbol> toSymbol(new Symbol<iConcept>(secondObj));

		shared_ptr<Num> repeatNumSymbol=symbolPair.GetRepeatNum();
		if(repeatNumSymbol==NULL)//Push back one pair.
		{			
			res.push_back(SymbolPair(fromSymbol,toSymbol));
		}
		else
		{
			int repeatNum;
			if(repeatNumSymbol->ToInt(repeatNum))//Push back <repeatNum> pairs
			{
				for (int i=0;i<repeatNum;++i)
				{
					res.push_back(SymbolPair(fromSymbol,toSymbol));
				}
			}
			else
			{
				res.push_back(SymbolPair(fromSymbol,toSymbol));
			}
		}

		return res;
	}

}

