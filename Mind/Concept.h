#pragma once
#include "InOut.h"
#include "../DataCollection/Word.h"
#include "ConceptEdge.h"
#include "CommonFunction.h"

namespace DataCollection
{
	class Word;
}

namespace Mind
{
	class ConceptInteractTable;
	class BaseConcept;
	class ConceptLevelTable;

	class  _MINDINOUT Concept
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

		vector<ConceptEdge> _forward; //Concepts that <me> is dependent on 
		vector<ConceptEdge> _backward;//Concepts that depend on <me>

		Color _color;
		
	public:
		Concept(void);
		~Concept(void);
		//Concept(std::string str);;
		Concept(shared_ptr<DataCollection::Word> word);

		virtual shared_ptr<Concept> Copy() const;
		bool Same(const shared_ptr<Concept> concept) const;

		std::string GetString() const {return _identity.str;}
		int GetId() const { return _identity.id; }
		void SetId(int val) { _identity.id = val; }

		vector<shared_ptr<Concept>> GetForwardConcepts()const;
		vector<shared_ptr<Concept>> GetBackwardConcepts()const;
		virtual void AddForwardConcept(const shared_ptr<Concept> concept,const double sensitivity=1);
		virtual void AddBackwardConcept(const shared_ptr<Concept> concept,const double sensitivity=1);
		//�����toConcept���������δ�
		void AddForwardModification(const shared_ptr<Concept> toConcept,const shared_ptr<Concept> modification);
		void AddBackwardModification(const shared_ptr<Concept> toConcept,const shared_ptr<Concept> modification);

		bool IsPartofSpeech(DataCollection::PartOfSpeech partofspeech) const;
		DataCollection::PartOfSpeech GetPartOfSpeech() const {return _partofspeech;}

		Color GetColor() const { return _color; }
		void SetColor(Color val) { _color = val; }

		shared_ptr<DataCollection::Word> GetWord() const ;

		//������<concept>�ϣ������໥�����б�
		//<me>��������concept��_forward����������<toConcept>,������<me>��<toConcept>�Ľ��͡�
		shared_ptr<ConceptInteractTable> InteractWith(const shared_ptr<Concept> toConcept) const;
		//<me>��BaseConcept��toConcept��BaseConcept֮����໥���á�
		shared_ptr<ConceptInteractTable> DeepInteractWith(const shared_ptr<Concept> toConcept) const;
		void DeepInteractWith(const shared_ptr<Concept> toConcept,vector<pair<shared_ptr<Mind::Concept>,shared_ptr<Mind::Concept>>>& pairs) const;

		//���BaseConcept��ֻ������toConcept�йص�Base������������modification�йص�Base��
		vector<shared_ptr<Concept>> GetBase() const ;
		virtual bool IsBaseConcept() const {return false;}

		shared_ptr<ConceptLevelTable> GetLevelTable() const;

	private:
		shared_ptr<DataCollection::Word> GetParticularWord(DataCollection::PartOfSpeech partofspeech) const;
		void Recursive_GetBase(const Concept* concept,vector<shared_ptr<Concept>>& result) const;
		void Recursive_GetEdgeInteractTable(const ConceptEdge& edge,shared_ptr<ConceptInteractTable> mod_table) const;
		void Recursive_SearchLevel( const Concept* concept,const int curLevel,shared_ptr<ConceptLevelTable> levelTable ) const;
	};
}


