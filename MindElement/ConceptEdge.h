#pragma once
#include "InOut.h"
#include "../MindInterface/iConceptEdge.h"

namespace Mind
{
	class iConceptInteractTable;
	class iConcept;
	class ConceptEdge : public iConceptEdge
	{
		shared_ptr<iConcept> _concept;
		vector<shared_ptr<iConcept>> _modification;//���δʣ���ʾ�����ӵ�concept�����ӵ�concept�Ĺ�ϵ������Ϊ��.
		double _sensitivity; //From -1 (negative) to 1(positive)
		
	public:
		ConceptEdge(void);
		~ConceptEdge(void);
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
		virtual vector<shared_ptr<iConcept>> GetModification() const;

		//����<_modification>��<_concept>������õ��б�
		virtual shared_ptr<iConceptInteractTable> GetSelfDeepInteract() const;
	};
}


