#pragma once
#include "InOut.h"
#include "../DataCollection/Word.h"
#include "ConceptEdge.h"

#include "../MindInterface/iConcept.h"
#include "../MindInterface/CommonFunction.h"

namespace DataCollection
{
	class Word;
}

namespace Mind
{
	class ConceptInteractTable_iConcept;
	class BaseConcept;
	class ConceptLevelTable;

	class  _MINDELEMENTINOUT Concept : public iConcept
	{
	public:
		enum Color
		{
			WHITE,
			BLACK
		};

	protected:
		Identity _identity;
		DataCollection::PartOfSpeech _partofspeech;

		vector<shared_ptr<iConceptEdge>> _forward; //Concepts that <me> is dependent on 
		vector<shared_ptr<iConceptEdge>> _backward;//Concepts that depend on <me>

		Color _color;
		
	public:
		Concept(void);
		virtual ~Concept(void);
		//Concept(std::string str);;
		Concept(const shared_ptr<DataCollection::Word> word);

		virtual shared_ptr<iConcept> Copy() const;
		virtual bool Same(const shared_ptr<iConcept> concept) const;

		virtual std::string GetString() const {return _identity.str;}
		virtual int GetId() const { return _identity.id; }
		virtual void SetId(int val) { _identity.id = val; }
		virtual Identity GetIdentity() const ; 

		virtual vector<shared_ptr<iConcept>> GetForwardConcepts()const;
		virtual vector<shared_ptr<iConcept>> GetBackwardConcepts()const;
		virtual void AddForwardConcept(const shared_ptr<iConcept> concept,const double sensitivity=1);
		virtual void AddBackwardConcept(const shared_ptr<iConcept> concept,const double sensitivity=1);
		//�����toConcept���������δ�
		virtual void AddForwardModification(const shared_ptr<iConcept> toConcept,const shared_ptr<iConcept> modification);
		virtual void AddBackwardModification(const shared_ptr<iConcept> toConcept,const shared_ptr<iConcept> modification);

		virtual DataCollection::PartOfSpeech GetPartOfSpeech() const {return _partofspeech;}

		Color GetColor() const { return _color; }
		void SetColor(Color val) { _color = val; }

		virtual shared_ptr<DataCollection::Word> GetWord() const ;

		//������<concept>�ϣ������໥�����б�
		//<me>��������concept��_forward����������<toConcept>,������<me>��<toConcept>�Ľ��͡�
		virtual shared_ptr<iConceptInteractTable> InteractWith(const shared_ptr<iConcept> toConcept) const;
		//<me>��BaseConcept��toConcept��BaseConcept֮����໥���á�
		virtual shared_ptr<iConceptInteractTable> DeepInteractWith(const shared_ptr<iConcept> toConcept) const;

		//���BaseConcept��ֻ������toConcept�йص�Base������������modification�йص�Base��
		virtual vector<shared_ptr<iConcept>> GetBase() const ;
		virtual bool IsBaseConcept() const {return false;}

		virtual shared_ptr<iConceptLevelTable> GetLevelTable() const;
		//Return the same class of <me>
		shared_ptr<Concept> Clone() const;

	private:
		shared_ptr<DataCollection::Word> GetParticularWord(DataCollection::PartOfSpeech partofspeech) const;
		void Recursive_GetBase(const iConcept* concept,vector<shared_ptr<iConcept>>& result) const;
		void Recursive_GetEdgeInteractTable(const shared_ptr<iConceptEdge>& edge,shared_ptr<iConceptInteractTable> mod_table) const;
		void Recursive_SearchLevel( const iConcept* concept,const int curLevel,shared_ptr<ConceptLevelTable> levelTable ) const;
		virtual const vector<shared_ptr<iConceptEdge>> GetForwardEdges() const ;
	};
}


