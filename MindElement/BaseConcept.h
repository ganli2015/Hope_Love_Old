#pragma once
#include "InOut.h"
#include "Concept.h"

namespace Mind
{
	class _MINDELEMENTINOUT BaseConcept : public Concept
	{
		//表示BaseConcept的唯一识别的id。
		int _baseId;
		
	public:
		BaseConcept(void);
		virtual ~BaseConcept(void);
		BaseConcept(shared_ptr<DataCollection::Word> word);

		virtual shared_ptr<iConcept> Copy() const;

		virtual bool IsBaseConcept() const {return true;}

		int GetBaseId() const { return _baseId; }
		void SetBaseId(int val) { _baseId = val; }

		virtual vector<shared_ptr<iConcept>> GetBase() const;
	private:
		virtual void AddForwardConcept(const shared_ptr<Concept> concept,const double sensitivity=1);
	};
}


