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

	///iConcept is a concept related with a word.
	///It contains knowledge about the meaning of the word and reflects how AI understand the word.
	///It has some relationship with other concepts.
	///
	///There are non-base concepts and base concepts.
	///Every non-base concept should depend on base concepts directly or indirectly.
	///Refer to BaseConcept for description about base concepts .
	class _MINDINTERFACEINOUT iConcept :public Obj<iConcept>
	{
	public:
		iConcept(void);
		virtual ~iConcept(void);

		///Copy <me>.
		///If <me> is a derived class, the returned object points to the derived class.
		virtual shared_ptr<iConcept> Copy() const =0;
		virtual bool Same(const shared_ptr<iConcept> concept) const =0;

		///Get the string of the word.
		virtual std::string GetString() const =0;

		///Get ID of <me>.
		///Refer to <Identity> for the meaning of ID.
		virtual int GetId() const =0;
		virtual void SetId(int val) =0;
		virtual Identity GetIdentity() const =0; 

		///Return concepts that <me> is dependent on.
		///Those concepts describe what <me> means.
		///They expose detailed information of <me>.
		virtual vector<shared_ptr<iConcept>> GetForwardConcepts()const =0;
		///Return concepts that depend on <me>.
		virtual vector<shared_ptr<iConcept>> GetBackwardConcepts()const =0;

		///Add concepts <me> depend on.
		///<concept> should describe what <me> means.
		///<sensitivity> is how strong <me> and <concept> are related with.
		virtual void AddForwardConcept(const shared_ptr<iConcept> concept,const double sensitivity=1) =0;
		///Add concepts that depend on <me>.
		virtual void AddBackwardConcept(const shared_ptr<iConcept> concept,const double sensitivity=1) =0;

		///Add modification of relationship between <me> and <toConcept>.
		///<modification> describe more detailed  information about how <me> depends on <toConcept>.
		virtual void AddForwardModification(const shared_ptr<iConcept> toConcept,const shared_ptr<iConcept> modification) =0;

		///Add modification of relationship between <me> and <toConcept>.
		///<modification> is a concept interaction table and  describe more complicated information about how <me> depends on <toConcept>.
		virtual void AddForwardModification(const shared_ptr<iConcept> toConcept,const shared_ptr<iConceptInteractTable> modification) =0;
		virtual void AddBackwardModification(const shared_ptr<iConcept> toConcept,const shared_ptr<iConcept> modification) =0;

		///Get POS of the word of <me>.
		virtual DataCollection::PartOfSpeech GetPartOfSpeech() const  =0;

		///Get the word of <me>.
		virtual shared_ptr<DataCollection::Word> GetWord() const  =0;

		///Interact <me> with <toConcept> and return the interaction table.
		///The interaction table reflects the relationship after interaction.
		///The interaction table is more superficial than one returned by <DeepInteractWith>.
		virtual shared_ptr<iConceptInteractTable> InteractWith(const shared_ptr<iConcept> toConcept) const =0;

		///Interact <me> with <toConcept> in a deeper way and return the interaction table.
		///The interaction table contains information of relationship between base concepts interaction of <me> and <toConcept>.
		virtual shared_ptr<iConceptInteractTable> DeepInteractWith(const shared_ptr<iConcept> toConcept) const =0;

		///Get base concepts that <me> depends on.
		///They include base concepts of forward concepts, excluding base concepts of modification concepts.
		virtual vector<shared_ptr<iConcept>> GetBase() const  =0;

		///Check whether <me> is a base concept.
		virtual bool IsBaseConcept() const  =0;

		///Get the level table of <me>.
		///Refer to <iConceptLevelTable> for the meaning of iConceptLevelTable.
		virtual shared_ptr<iConceptLevelTable> GetLevelTable() const  =0;

		///Get the concept edges of <me>.
		///Refer to <iConceptEdge> for the meaning of iConceptEdge.
		virtual const vector<shared_ptr<iConceptEdge>> GetForwardEdges() const =0;	

		///Check whether <description> matches with one of modifications of forward concepts of <me>.
		///Only if <description> and modification are totally the same, then return true.
		virtual bool MatchWithDescription(const shared_ptr<iConceptInteractTable> description) const =0;
		///Check whether <description> matches with one of modifications of forward concepts of <me>.
		///Only if <description> and modification are totally the same, then return true.
		///Return the first matched <toConcept>.
		virtual bool MatchWithDescription(const shared_ptr<iConceptInteractTable> description,shared_ptr<iConcept>& toConcept) const =0;
protected:
	};
}


