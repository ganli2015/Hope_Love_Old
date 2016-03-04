#pragma once
#include "InOut.h"

namespace Mind
{
	class ConceptInteractTable;
	class Concept;
	class ConceptEdge
	{
		shared_ptr<Concept> _concept;
		vector<shared_ptr<Concept>> _modification;//���δʣ���ʾ�����ӵ�concept�����ӵ�concept�Ĺ�ϵ������Ϊ��.
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

		//����<_modification>��<_concept>������õ��б�
		shared_ptr<ConceptInteractTable> GetSelfDeepInteract() const;
	};
}


