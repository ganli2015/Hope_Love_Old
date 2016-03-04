#include "StdAfx.h"
#include "Concept.h"
#include "ConceptInteractTable.h"
#include "ConceptLevelTable.h"

#include "../DataCollection/Word.h"
#include "../DataCollection/DataBaseProcessorTool.h"

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

	Concept::Concept(shared_ptr<DataCollection::Word> word)
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

	bool Concept::IsPartofSpeech( DataCollection::PartOfSpeech partofspeech ) const
	{
		return partofspeech==_partofspeech;
	}

	shared_ptr<DataCollection::Word> Concept::GetParticularWord( DataCollection::PartOfSpeech partofspeech ) const
	{
		return DataBaseProcessorTool::GetParticularWord(_identity.str,partofspeech);
	}

	vector<shared_ptr<Concept>> Concept::GetForwardConcepts() const
	{
		vector<shared_ptr<Concept>> res;
		for (unsigned int i=0;i<_forward.size();++i)
		{
			res.push_back(_forward[i].GetConcept());
		}
		return res;
	}

	vector<shared_ptr<Concept>> Concept::GetBackwardConcepts() const
	{
		vector<shared_ptr<Concept>> res;
		for (unsigned int i=0;i<_backward.size();++i)
		{
			res.push_back(_backward[i].GetConcept());
		}
		return res;
	}

	void Concept::AddForwardConcept( const shared_ptr<Concept> concept,const double sensitivity/*=1*/ )
	{
		ConceptEdge edge(concept,sensitivity);
		_forward.push_back(edge);
	}

	void Concept::AddBackwardConcept( const shared_ptr<Concept> concept,const double sensitivity/*=1*/ )
	{
		ConceptEdge edge(concept,sensitivity);
		_backward.push_back(edge);
	}

	class find_conceptEdge
	{
		shared_ptr<Concept> _target;
	public:
		find_conceptEdge(const shared_ptr<Concept> target):_target(target)
		{

		}
		~find_conceptEdge(){}

		bool operator()(const ConceptEdge& edge)
		{
			shared_ptr<Concept> concept=edge.GetConcept();
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

	void Concept::AddForwardModification( const shared_ptr<Concept> toConcept,const shared_ptr<Concept> modification )
	{
		vector<ConceptEdge>::iterator it=find_if(_forward.begin(),_forward.end(),find_conceptEdge(toConcept));
		if(it==_forward.end())
		{
			throw runtime_error("Error in AddModification: not find concept in conceptEdges!");
		}
		else
		{
			it->AddModification(modification);
		}
	}

	void Concept::AddBackwardModification( const shared_ptr<Concept> fromConcept,const shared_ptr<Concept> modification )
	{
		vector<ConceptEdge>::iterator it=find_if(_backward.begin(),_backward.end(),find_conceptEdge(fromConcept));
		if(it==_backward.end())
		{
			throw runtime_error("Error in AddModification: not find concept in conceptEdges!");
		}
		else
		{
			it->AddModification(modification);
		}
	}

	shared_ptr<Word> Concept::GetWord() const
	{
		return GetParticularWord(_partofspeech);
	}

	shared_ptr<ConceptInteractTable> Concept::InteractWith( const shared_ptr<Concept> toConcept ) const
	{
		class BuildInteractTable
		{
			shared_ptr<ConceptInteractTable> _table;
			shared_ptr<Concept> _to;//to concept

		public:
			BuildInteractTable(const shared_ptr<ConceptInteractTable> table,const shared_ptr<Concept> to):_table(table),_to(to){}
			~BuildInteractTable(){}

			void operator()(const ConceptEdge& edge)
			{
				//处理解释词和toConcept的关系
				shared_ptr<Concept> interept=edge.GetConcept();
				_table->Add(interept,_to);

				//处理修饰词和解释词的关系
				vector<shared_ptr<Concept>> modifications=edge.GetModification();
				for (unsigned int i=0;i<modifications.size();++i)
				{
					_table->Add(modifications[i],interept);
				}
			} 
		};

		shared_ptr<ConceptInteractTable> table(new ConceptInteractTable);
		for_each(_forward.begin(),_forward.end(),BuildInteractTable(table,toConcept));

		return table;
	}

	shared_ptr<ConceptInteractTable> Concept::DeepInteractWith( const shared_ptr<Concept> toConcept ) const
	{
		vector<shared_ptr<Concept>> myBase=GetBase();
		vector<shared_ptr<Concept>> base_to=toConcept->GetBase();
		shared_ptr<ConceptInteractTable> res(new ConceptInteractTable());
		CommonFunction::AppendToInteractTable(myBase,base_to,res);

		//添加_forward对<me>的作用
		for (unsigned int i=0;i<_forward.size();++i)
		{
			shared_ptr<ConceptInteractTable> mod_table(new ConceptInteractTable());
			Recursive_GetEdgeInteractTable(_forward[i],mod_table);
			res->Absorb(mod_table);
		}

		//添加toConcept的_forward对toConcept的作用
		for (unsigned int i=0;i<toConcept->_forward.size();++i)
		{
			shared_ptr<ConceptInteractTable> mod_table(new ConceptInteractTable());
			Recursive_GetEdgeInteractTable(toConcept->_forward[i],mod_table);
			res->Absorb(mod_table);
		}

		return res;
	}

	void Concept::DeepInteractWith(const shared_ptr<Concept> toConcept,vector<pair<shared_ptr<Mind::Concept>,shared_ptr<Mind::Concept>>>& pairs) const
	{
		pairs=DeepInteractWith(toConcept)->GetAllRelations();
	}

	void Concept::Recursive_GetEdgeInteractTable(const ConceptEdge& edge,shared_ptr<ConceptInteractTable> mod_table) const
	{
		mod_table->Absorb(edge.GetSelfDeepInteract());

		//递归地建立toConcep所依赖的每个Edge的Table
		vector<ConceptEdge> forwardEdges=edge.GetConcept()->_forward;		
		for (unsigned int i=0;i<forwardEdges.size();++i)
		{
			Recursive_GetEdgeInteractTable(forwardEdges[i],mod_table);
		}

		//递归地建立modification所依赖的每个Edge的Table
		vector<shared_ptr<Concept>> mods=edge.GetModification();
		for (unsigned int i=0;i<mods.size();++i)
		{
			for (unsigned int j=0;j<mods[i]->_forward.size();++j)
			{
				Recursive_GetEdgeInteractTable(mods[i]->_forward[j],mod_table);
			}
		}
	}

	vector<shared_ptr<Concept>> Concept::GetBase() const
	{
		vector<shared_ptr<Concept>> res;
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

	void Concept::Recursive_GetBase( const Concept* concept,vector<shared_ptr<Concept>>& result ) const
	{
		vector<ConceptEdge> edges=concept->_forward;
		for (unsigned int i=0;i<edges.size();++i)
		{
			shared_ptr<Concept> toConcept=edges[i].GetConcept();
			if(toConcept->IsBaseConcept())
			{
				result.push_back(toConcept);
			}
			else
			{
				if(toConcept->_forward.empty())//如果toConcept不是BaseConcept同时没有所依赖的Concept，抛出异常。因为每个“叶”必须是BaseConcept。
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

	shared_ptr<Concept> Concept::Copy() const
	{
		shared_ptr<Concept> res(new Concept());
		res->_backward=_backward;
		res->_forward=_forward;
		res->_color=_color;
		res->_identity=_identity;
		res->_partofspeech=_partofspeech;

		return res;
	}

	bool Concept::Same( const shared_ptr<Concept> concept ) const
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

	shared_ptr<ConceptLevelTable> Concept::GetLevelTable() const
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

	void Concept::Recursive_SearchLevel( const Concept* concept,const int curLevel,shared_ptr<ConceptLevelTable> levelTable ) const
	{
		int nextLevel=curLevel+1;

		vector<ConceptEdge> edges=concept->_forward;
		for (unsigned int i=0;i<edges.size();++i)
		{
			shared_ptr<Concept> toConcept=edges[i].GetConcept();
			if(toConcept->IsBaseConcept())
			{
				levelTable->Insert(toConcept,nextLevel);
			}
			else
			{
				if(toConcept->_forward.empty())//如果toConcept不是BaseConcept同时没有所依赖的Concept，抛出异常。因为每个“叶”必须是BaseConcept。
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

}

