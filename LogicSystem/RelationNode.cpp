#include "StdAfx.h"
#include "RelationNode.h"

#include "../MindInterface/iConcept.h"
#include "../MindInterface/iExpression.h"
#include "../MindInterface/iConceptInteractTable.h"

#include "../MindInterface/iMindElementCreator.h"


using namespace Mind;

namespace LogicSystem
{
	RelationNode::RelationNode(void):_andTag("&&"),_orTag("||")
	{
	}


	RelationNode::~RelationNode(void)
	{
	}

	std::string RelationNode::GetString() const
	{
		string res="";

		for (unsigned int i=0;i<_subRelations.size();++i)
		{
			res+='(';
			res+=_subRelations[i]->GetString();
			res+=')';

			if(i!=_subRelations.size()-1)
			{
				if(_state==And)
				{
					res+=_andTag;
				}
				else
				{
					res+=_orTag;
				}
			}
		}

		return res;
	}

	bool RelationNode::Satisfy( const shared_ptr<iExpression> expre )
	{
		shared_ptr<Mind::iConceptInteractTable> interTable=expre->GetProtoInteractTable();
		
		return InterTableSatisfyRelation(interTable);
	}

	bool RelationNode::InterTableSatisfyRelation( const shared_ptr<Mind::iConceptInteractTable> interTable )
	{
		vector<iRelation::PairSequence> matchedPairSequences=FindMatchedPairSequence(interTable->GetAllRelations());
		if(matchedPairSequences.empty())
		{
			_satisfiedSequence.clear();

			return false;
		}
		else
		{
			_satisfiedSequence=matchedPairSequences.front();

			return true;
		}

// 		for (unsigned int i=0;i<matchedPairSequences.size();++i)
// 		{
// 			if(SatifyConstraint(matchedPairSequences[i],_constraints))//Any of them satisfies ,then we consider <expre> satisfying.
// 			{
// 				_satisfiedSequence=matchedPairSequences[i];
// 
// 				return true;
// 			}
// 		}
// 
// 		_satisfiedSequence.clear();
// 
// 		return false;
	}

	vector<iRelation::PairSequence> RelationNode::FindMatchedPairSequence( const vector<ConceptPair>& conceptPairs ) const
	{
		vector<iRelation::PairSequence> res;
		Recursive_FindMatchedPairSequence(conceptPairs,_subRelations,res);

		RemoveSequencesUnsatifyConstraints(_constraints,res);

		return res;
	}

	void RelationNode::Recursive_FindMatchedPairSequence( const vector<ConceptPair>& conceptPairs, 
		const vector<shared_ptr<iRelation>>& relations, 
		vector<PairSequence>& sequences ) const
	{
		if(relations.empty()) return;

		sequences.clear();
		//Extract the matched pairs of the first relation, and remove the corresponding concept pairs in <conceptPairs>.
		//Note, there are several possibilities of PairSequence.
		vector<PairSequence> firstSeq=relations.front()->FindMatchedPairSequence(conceptPairs);
		vector<shared_ptr<iRelation>> remainRelation(relations.begin()+1,relations.end());

		if(remainRelation.empty())//If <relations.front()> is the last relation, then push back all <firstSeq> to <sequences>.
		{
			sequences.insert(sequences.end(),firstSeq.begin(),firstSeq.end());
			return;
		}

		for (unsigned int i=0;i<firstSeq.size();++i)
		{
			vector<ConceptPair> remainPairs=ExcludeConceptPairsFromSequence(conceptPairs,firstSeq[i]);
			vector<PairSequence> subSequence;
			//Search for the remaining relations.
			Recursive_FindMatchedPairSequence(remainPairs,remainRelation,subSequence);

			if(_state==And && !subSequence.empty())//if <subSequence> is empty, it means that there is at least one relation not satisfied in remaining relations and it fails to satisfy AND condition.
			{
				vector<PairSequence> combinedSeqs=CombineOneSeqWithManySeqs(firstSeq[i],subSequence);
				sequences.insert(sequences.end(),combinedSeqs.begin(),combinedSeqs.end());
			}
			else if(_state==Or)
			{
				vector<PairSequence> combinedSeqs=CombineOneSeqWithManySeqs(firstSeq[i],subSequence);
				sequences.insert(sequences.end(),combinedSeqs.begin(),combinedSeqs.end());
			}
		}
	}

	vector<iRelation::ConceptPair> RelationNode::ExcludeConceptPairsFromSequence( const vector<ConceptPair>& rawPairs,PairSequence sequence ) const
	{
		vector<iRelation::ConceptPair> res;
		for (unsigned int i=0;i<rawPairs.size();++i)
		{
			if(!ConceptPairInSequenceAndRemovePair(rawPairs[i],sequence))
			{
				res.push_back(rawPairs[i]);
			}
		}

		return res;
	}

	bool RelationNode::ConceptPairInSequenceAndRemovePair( const ConceptPair& cPair,PairSequence& sequence ) const
	{
		class FindCPair
		{
			ConceptPair _cPair;
		public:
			FindCPair(const ConceptPair& val):_cPair(val){}
			~FindCPair(){}

			bool operator()(const iRelation::PairInfo info)
			{
				if(info.cPair.first->Same(_cPair.first) && info.cPair.second->Same(_cPair.second))
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		};

		vector<PairInfo>::const_iterator pairIter=find_if(sequence.begin(),sequence.end(),FindCPair(cPair));
		if(pairIter==sequence.end())
		{
			return false;
		}
		else
		{
			sequence.erase(pairIter);
			return true;
		}
	}

	vector<iRelation::PairSequence> RelationNode::CombineOneSeqWithManySeqs( const PairSequence& oneSeq,
		const vector<PairSequence>& manySeqs ) const
	{
		vector<iRelation::PairSequence> res;
		if(manySeqs.empty())
		{
			res.push_back(oneSeq);
			return res;
		}

		res.reserve(manySeqs.size());
		for (unsigned int i=0;i<manySeqs.size();++i)
		{
			PairSequence newSeq=oneSeq;
			newSeq.insert(newSeq.end(),manySeqs[i].begin(),manySeqs[i].end());
			res.push_back(newSeq);
		}

		return res;
	}

	void RelationNode::AddConstraint( const shared_ptr<iRelationConstraint> constraint )
	{
		_constraints.push_back(constraint);
	}

	shared_ptr<iRelation> RelationNode::GenerateSpecialRelation() const
	{
		shared_ptr<iRelationNode> res(new RelationNode());
		res->SetState(_state);

		for (unsigned int i=0;i<_subRelations.size();++i)
		{
			shared_ptr<iRelation> subRelation=_subRelations[i]->GenerateSpecialRelation();
			if(subRelation==NULL)
			{
				return NULL;
			}
			else
			{
				res->AddSubRelation(subRelation);
			}
		}

		return res;
	}

	shared_ptr<Mind::iConceptInteractTable> RelationNode::GenerateConceptTable() const
	{
		shared_ptr<Mind::iConceptInteractTable> res=iMindElementCreator::CreateConceptInteractTable();
		for (unsigned int i=0;i<_subRelations.size();++i)
		{
			shared_ptr<Mind::iConceptInteractTable> subTable=_subRelations[i]->GenerateConceptTable();
			res->Absorb(subTable);
		}

		return res;
	}

}

