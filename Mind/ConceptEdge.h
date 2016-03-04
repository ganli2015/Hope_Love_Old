#pragma once
#include "InOut.h"

namespace Mind
{
	class ConceptInteractTable;
	class Concept;
	class ConceptEdge
	{
		shared_ptr<Concept> _concept;
		vector<shared_ptr<Concept>> _modification;//修饰词，表示被连接的concept与连接的concept的关系，可以为空.
		double _sensitivity; //From -1 (negative) to 1(positive)
		
	public:
		ConceptEdge(void);
		~ConceptEdge(void);
		ConceptEdge(const shared_ptr<Concept> concept);
		ConceptEdge(const shared_ptr<Concept> concept,const double sensi);

		shared_ptr<Concept> GetConcept() const;
		double GetSensitivity() const { return _sensitivity; }
		//From -1 (negative) to 1(positive)
		void SetSensitivity(double val) 
		{
			if(abs(val)>1)
			{
				throw runtime_error("Sensitivity must be between -1 and 1 !!");
			}
			_sensitivity = val;
		}

		void AddModification(const shared_ptr<Concept> modification);
		vector<shared_ptr<Concept>> GetModification() const;

		//建立<_modification>对<_concept>深度作用的列表
		shared_ptr<ConceptInteractTable> GetSelfDeepInteract() const;
	};
}


