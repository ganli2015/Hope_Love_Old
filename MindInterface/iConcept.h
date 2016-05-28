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

		///�����toConcept���������δ�
		virtual void AddForwardModification(const shared_ptr<iConcept> toConcept,const shared_ptr<iConcept> modification) =0;
		virtual void AddForwardModification(const shared_ptr<iConcept> toConcept,const shared_ptr<iConceptInteractTable> modification) =0;
		virtual void AddBackwardModification(const shared_ptr<iConcept> toConcept,const shared_ptr<iConcept> modification) =0;

		virtual DataCollection::PartOfSpeech GetPartOfSpeech() const  =0;

		virtual shared_ptr<DataCollection::Word> GetWord() const  =0;

		///������<concept>�ϣ������໥�����б�
		///<me>��������concept��_forward����������<toConcept>,������<me>��<toConcept>�Ľ��͡�
		virtual shared_ptr<iConceptInteractTable> InteractWith(const shared_ptr<iConcept> toConcept) const =0;
		//<me>��BaseConcept��toConcept��BaseConcept֮����໥���á�
		virtual shared_ptr<iConceptInteractTable> DeepInteractWith(const shared_ptr<iConcept> toConcept) const =0;

		///���BaseConcept��ֻ������toConcept�йص�Base������������modification�йص�Base��
		virtual vector<shared_ptr<iConcept>> GetBase() const  =0;
		virtual bool IsBaseConcept() const  =0;

		virtual shared_ptr<iConceptLevelTable> GetLevelTable() const  =0;
		virtual const vector<shared_ptr<iConceptEdge>> GetForwardEdges() const =0;		
protected:
	};
}


