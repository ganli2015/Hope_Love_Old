#include "StdAfx.h"
#include "Concept.h"
#include "ConceptInteractTable_iConcept.h"
#include "ConceptLevelTable.h"

#include "../DataCollection/Word.h"
#include "../DataCollection/LanguageFunc.h"

using namespace DataCollection;
using namespace std;
namespace Mind
{
	Concept::Concept(void):_partofspeech(Unknown)
	{
		_identity.id=0;
	}


	Concept::~Concept(void)
	{
		//DeleteVectorPtr(_adjWord);
	}

	Concept::Concept(const shared_ptr<DataCollection::Word> word)
	{
		_identity.str=word->GetString();
		_identity.id=0;
		_partofspeech=word->Type();
	}

// 	Concept::Concept( std::string str ) 
// 	{
// 		_identity.str=str;
// 		_identity.id=0;
// 		_partofspeech=Unknown;
// 	}

	shared_ptr<DataCollection::Word> Concept::GetParticularWord( DataCollection::PartOfSpeech partofspeech ) const
	{
		return LanguageFunc::GetParticularWord(_identity.str,partofspeech);
	}

	vector<shared_ptr<iConcept>> Concept::GetForwardConcepts() const
	{
		vector<shared_ptr<iConcept>> res;
		for (unsigned int i=0;i<_forward.size();++i)
		{
			res.push_back(_forward[i]->GetConcept());
		}
		return res;
	}

	vector<shared_ptr<iConcept>> Concept::GetBackwardConcepts() const
	{
		vector<shared_ptr<iConcept>> res;
		for (unsigned int i=0;i<_backward.size();++i)
		{
			res.push_back(_backward[i]->GetConcept());
		}
		return res;
	}

	void Concept::AddForwardConcept( const shared_ptr<iConcept> concept,const double sensitivity/*=1*/ )
	{
		Check(concept->GetPartOfSpeech()==Noun ||concept->GetPartOfSpeech()==_partofspeech);

		shared_ptr<ConceptEdge> edge(new ConceptEdge(concept,sensitivity));
		_forward.push_back(edge);
	}

	void Concept::AddBackwardConcept( const shared_ptr<iConcept> concept,const double sensitivity/*=1*/ )
	{
		shared_ptr<ConceptEdge> edge(new ConceptEdge(concept,sensitivity));
		_backward.push_back(edge);
	}

	class find_conceptEdge
	{
		shared_ptr<iConcept> _target;
	public:
		find_conceptEdge(const shared_ptr<iConcept> target):_target(target)
		{

		}
		~find_conceptEdge(){}

		bool operator()(const shared_ptr<iConceptEdge>& edge)
		{
			shared_ptr<iConcept> concept=edge->GetConcept();
			if(concept->GetId()==_target->GetId() && concept->GetString()==_target->GetString())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	};

	void Concept::AddForwardModification( const shared_ptr<iConcept> toConcept,const shared_ptr<iConcept> modification )
	{
		vector<shared_ptr<iConceptEdge>>::iterator it=find_if(_forward.begin(),_forward.end(),find_conceptEdge(toConcept));
		if(it==_forward.end())
		{
			throw runtime_error("Error in AddModification: not find concept in conceptEdges!");
		}
		else
		{
			(*it)->AddModification(modification);
		}
	}

	void Concept::AddForwardModification( const shared_ptr<iConcept> toConcept,const shared_ptr<iConceptInteractTable> modification )
	{
		vector<shared_ptr<iConceptEdge>>::iterator it=find_if(_forward.begin(),_forward.end(),find_conceptEdge(toConcept));
		if(it==_forward.end())
		{
			throw runtime_error("Error in AddModification: not find concept in conceptEdges!");
		}
		else
		{
			(*it)->AddModification(modification);
		}
	}

	void Concept::AddBackwardModification( const shared_ptr<iConcept> fromConcept,const shared_ptr<iConcept> modification )
	{
		vector<shared_ptr<iConceptEdge>>::iterator it=find_if(_backward.begin(),_backward.end(),find_conceptEdge(fromConcept));
		if(it==_backward.end())
		{
			throw runtime_error("Error in AddModification: not find concept in conceptEdges!");
		}
		else
		{
			(*it)->AddModification(modification);
		}
	}

	shared_ptr<Word> Concept::GetWord() const
	{
		return GetParticularWord(_partofspeech);
	}

	shared_ptr<iConceptInteractTable> Concept::InteractWith( const shared_ptr<iConcept> toConcept ) const
	{
		class BuildInteractTable
		{
			shared_ptr<ConceptInteractTable_iConcept> _table;
			shared_ptr<iConcept> _to;//to concept

		public:
			BuildInteractTable(const shared_ptr<ConceptInteractTable_iConcept> table,const shared_ptr<iConcept> to):_table(table),_to(to){}
			~BuildInteractTable(){}

			void operator()(const shared_ptr<iConceptEdge>& edge)
			{
				//处理解释词和toConcept的关系
				shared_ptr<iConcept> interept=edge->GetConcept();
				_table->Add(interept,_to);

				//处理修饰词和解释词的关系
				vector<MindType::ConceptPair> modifications=edge->GetModification()->GetAllRelations();
				for (unsigned int i=0;i<modifications.size();++i)
				{
					_table->Add(modifications[i].first,modifications[i].second);
				}
			} 
		};

		shared_ptr<ConceptInteractTable_iConcept> table(new ConceptInteractTable_iConcept);
		for_each(_forward.begin(),_forward.end(),BuildInteractTable(table,toConcept));

		return table;
	}

	shared_ptr<iConceptInteractTable> Concept::DeepInteractWith( const shared_ptr<iConcept> toConcept ) const
	{
		vector<shared_ptr<iConcept>> myBase=GetBase();
		vector<shared_ptr<iConcept>> base_to=toConcept->GetBase();
		shared_ptr<ConceptInteractTable_iConcept> res(new ConceptInteractTable_iConcept());
		CommonFunction::AppendToInteractTable(myBase,base_to,res);

		//添加_forward对<me>的作用
		for (unsigned int i=0;i<_forward.size();++i)
		{
			shared_ptr<ConceptInteractTable_iConcept> mod_table(new ConceptInteractTable_iConcept());
			Recursive_GetEdgeInteractTable(_forward[i],mod_table);
			res->Absorb(mod_table);
		}

		//添加toConcept的_forward对toConcept的作用
		for (unsigned int i=0;i<toConcept->GetForwardEdges().size();++i)
		{
			shared_ptr<ConceptInteractTable_iConcept> mod_table(new ConceptInteractTable_iConcept());
			Recursive_GetEdgeInteractTable(toConcept->GetForwardEdges()[i],mod_table);
			res->Absorb(mod_table);
		}

		return res;
	}

	void Concept::Recursive_GetEdgeInteractTable(const shared_ptr<iConceptEdge>& edge,shared_ptr<iConceptInteractTable> mod_table) const
	{
		shared_ptr<iConceptInteractTable> selfTable=edge->GetSelfDeepInteract();
		mod_table->Absorb(selfTable);

		//递归地建立toConcep所依赖的每个Edge的Table
		vector<shared_ptr<iConceptEdge>> forwardEdges=edge->GetConcept()->GetForwardEdges();		
		for (unsigned int i=0;i<forwardEdges.size();++i)
		{
			Recursive_GetEdgeInteractTable(forwardEdges[i],mod_table);
		}

		//递归地建立modification所依赖的每个Edge的Table
		vector<MindType::ConceptPair> mods=edge->GetModification()->GetAllRelations();
		for (unsigned int i=0;i<mods.size();++i)
		{
			vector<shared_ptr<iConceptEdge>> from_edges=mods[i].first->GetForwardEdges();
			for (unsigned int j=0;j<from_edges.size();++j)
			{
				Recursive_GetEdgeInteractTable(from_edges[j],mod_table);
			}

			vector<shared_ptr<iConceptEdge>> to_edges=mods[i].second->GetForwardEdges();
			for (unsigned int j=0;j<to_edges.size();++j)
			{
				Recursive_GetEdgeInteractTable(to_edges[j],mod_table);
			}
		}
	}

	vector<shared_ptr<iConcept>> Concept::GetBase() const
	{
		vector<shared_ptr<iConcept>> res;
		if(IsBaseConcept())
		{
			res.push_back(this->Copy());
		}
		else
		{
			Recursive_GetBase(this,res);
		}

		return res;
	}

	void Concept::Recursive_GetBase( const iConcept* concept,vector<shared_ptr<iConcept>>& result ) const
	{
		vector<shared_ptr<iConceptEdge>> edges=concept->GetForwardEdges();
		for (unsigned int i=0;i<edges.size();++i)
		{
			shared_ptr<iConcept> toConcept=edges[i]->GetConcept();
			if(toConcept->IsBaseConcept())
			{
				result.push_back(toConcept);
			}
			else
			{
				if(toConcept->GetForwardEdges().empty())//如果toConcept不是BaseConcept同时没有所依赖的Concept，抛出异常。因为每个“叶”必须是BaseConcept。
				{
					throw logic_error(toConcept->GetString()+" has no base!!");
				}
				else
				{
					Recursive_GetBase(toConcept.get(),result);
				}
			}
		}
	}

	shared_ptr<iConcept> Concept::Copy() const
	{
		return Clone();
	}

	bool Concept::Same( const shared_ptr<iConcept> concept ) const
	{
		if(_identity.str==concept->GetString() && _identity.id==concept->GetId())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	shared_ptr<iConceptLevelTable> Concept::GetLevelTable() const
	{
		shared_ptr<ConceptLevelTable> res(new ConceptLevelTable(Copy()));
		if(IsBaseConcept())
		{
			res->Insert(Copy(),0);
		}
		else
		{
			Recursive_SearchLevel(this,0,res);
		}

		return res;
	}

	void Concept::Recursive_SearchLevel( const iConcept* concept,const int curLevel,shared_ptr<ConceptLevelTable> levelTable ) const
	{
		int nextLevel=curLevel+1;

		vector<shared_ptr<iConceptEdge>> edges=concept->GetForwardEdges();
		for (unsigned int i=0;i<edges.size();++i)
		{
			shared_ptr<iConcept> toConcept=edges[i]->GetConcept();
			if(toConcept->IsBaseConcept())
			{
				levelTable->Insert(toConcept,nextLevel);
			}
			else
			{
				if(toConcept->GetForwardEdges().empty())//如果toConcept不是BaseConcept同时没有所依赖的Concept，抛出异常。因为每个“叶”必须是BaseConcept。
				{
					throw logic_error(toConcept->GetString()+" has no base!!");
				}
				else
				{
					Recursive_SearchLevel(toConcept.get(),nextLevel,levelTable);
				}
			}
		}
	}

	const vector<shared_ptr<iConceptEdge>> Concept::GetForwardEdges() const
	{
		return _forward;
	}

	shared_ptr<Concept> Concept::Clone() const
	{
		shared_ptr<Concept> res(new Concept());
		res->_backward=_backward;
		res->_forward=_forward;
		res->_color=_color;
		res->_identity=_identity;
		res->_partofspeech=_partofspeech;

		return res;
	}

	Mind::Identity Concept::GetIdentity() const
	{
		Identity id;
		id.id=GetId();
		id.str=GetString();

		return id;
	}

	bool Concept::MatchWithDescription( const shared_ptr<iConceptInteractTable> description ) const
	{
		for (unsigned int i=0;i<_forward.size();++i)
		{
			if(_forward[i]->MatchWithConceptTable(description))
			{
				return true;
			}
		}

		return false;
	}

	bool Concept::MatchWithDescription( const shared_ptr<iConceptInteractTable> description,shared_ptr<iConcept>& toConcept ) const
	{
		for (unsigned int i=0;i<_forward.size();++i)
		{
			if(_forward[i]->MatchWithConceptTable(description,toConcept))
			{
				return true;
			}
		}

		return false;
	}

}

