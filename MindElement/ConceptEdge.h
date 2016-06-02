#pragma once
#include "InOut.h"
#include "../MindInterface/iConceptEdge.h"

namespace Mind
{
	class iConceptInteractTable;
	class iConcept;
	class ConceptEdge : public iConceptEdge
	{
		weak_ptr<iConcept> _concept;
		shared_ptr<iConceptInteractTable> _modTable;
		//vector<weak_ptr<iConcept>> _modification;//修饰词，表示被连接的concept与连接的concept的关系，可以为空.
		double _sensitivity; //From -1 (negative) to 1(positive)
		
	public:
		ConceptEdge(void);
		virtual ~ConceptEdge(void);
		ConceptEdge(const shared_ptr<iConcept> concept);
		ConceptEdge(const shared_ptr<iConcept> concept,const double sensi);

		virtual shared_ptr<iConcept> GetConcept() const;
		virtual double GetSensitivity() const { return _sensitivity; }
		//From -1 (negative) to 1(positive)
		virtual void SetSensitivity(double val) 
		{
			if(abs(val)>1)
			{
				throw runtime_error("Sensitivity must be between -1 and 1 !!");
			}
			_sensitivity = val;
		}

		virtual void AddModification(const shared_ptr<iConcept> modification);
		virtual void AddModification(const shared_ptr<iConceptInteractTable> table) ;

		//virtual vector<shared_ptr<iConcept>> GetModification() const;
		virtual shared_ptr<iConceptInteractTable> GetModification() const ;

		//建立<_modification>对<_concept>深度作用的列表
		virtual shared_ptr<iConceptInteractTable> GetSelfDeepInteract() const;

		virtual bool MatchWithConceptTable(const shared_ptr<iConceptInteractTable> description) const ;
		virtual bool MatchWithConceptTable(const shared_ptr<iConceptInteractTable> description,shared_ptr<iConcept>& toConcept) const ;
	private:
		void Init() ;
	};
}


