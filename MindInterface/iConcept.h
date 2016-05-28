#pragma once
#include "InOut.h"

namespace DataCollection
{
	class Word;
	enum PartOfSpeech;
}

namespace Mind
{
	class iConceptInteractTable;
	class BaseConcept;
	class iConceptLevelTable;
	class iConceptEdge;
	struct Identity;

	class _MINDINTERFACEINOUT iConcept :public MyObject
	{
	public:
		iConcept(void);
		virtual ~iConcept(void);

		virtual shared_ptr<iConcept> Copy() const =0;
		virtual bool Same(const shared_ptr<iConcept> concept) const =0;

		virtual std::string GetString() const =0;
		virtual int GetId() const =0;
		virtual void SetId(int val) =0;
		virtual Identity GetIdentity() const =0; 

		///Return concepts that <me> is dependent on 
		virtual vector<shared_ptr<iConcept>> GetForwardConcepts()const =0;
		///Return concepts that depend on <me>
		virtual vector<shared_ptr<iConcept>> GetBackwardConcepts()const =0;
		virtual void AddForwardConcept(const shared_ptr<iConcept> concept,const double sensitivity=1) =0;
		virtual void AddBackwardConcept(const shared_ptr<iConcept> concept,const double sensitivity=1) =0;

		///添加与toConcept关联的修饰词
		virtual void AddForwardModification(const shared_ptr<iConcept> toConcept,const shared_ptr<iConcept> modification) =0;
		virtual void AddForwardModification(const shared_ptr<iConcept> toConcept,const shared_ptr<iConceptInteractTable> modification) =0;
		virtual void AddBackwardModification(const shared_ptr<iConcept> toConcept,const shared_ptr<iConcept> modification) =0;

		virtual DataCollection::PartOfSpeech GetPartOfSpeech() const  =0;

		virtual shared_ptr<DataCollection::Word> GetWord() const  =0;

		///作用于<concept>上，产生相互作用列表。
		///<me>所依赖的concept（_forward）会作用于<toConcept>,表明对<me>对<toConcept>的解释。
		virtual shared_ptr<iConceptInteractTable> InteractWith(const shared_ptr<iConcept> toConcept) const =0;
		//<me>的BaseConcept与toConcept的BaseConcept之间的相互作用。
		virtual shared_ptr<iConceptInteractTable> DeepInteractWith(const shared_ptr<iConcept> toConcept) const =0;

		///获得BaseConcept。只会获得与toConcept有关的Base，而不会获得与modification有关的Base。
		virtual vector<shared_ptr<iConcept>> GetBase() const  =0;
		virtual bool IsBaseConcept() const  =0;

		virtual shared_ptr<iConceptLevelTable> GetLevelTable() const  =0;
		virtual const vector<shared_ptr<iConceptEdge>> GetForwardEdges() const =0;		
protected:
	};
}


