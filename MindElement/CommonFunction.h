#pragma once
#include "InOut.h"

namespace Mind
{
	struct Identity
	{
		string str;
		//��ʾͬһ��string����Ӧ�Ĳ�ͬ��concept�������ʵ�id����-1��
		//Ŀǰͬһ�����ʵ�ͬһ������ֻ��Ӧ��һ��id��
		//Ҳ����˵���id��ʱ�𲻵����ã�
		int id;
	};

	class Concept;
	class ConceptInteractTable;
	class ConceptChain;
	namespace CommonFunction
	{
		//��<from>��<to>�������໥���ö���ӵ�table
		void AppendToInteractTable(const vector<shared_ptr<Concept>>& from,const vector<shared_ptr<Concept>>& to,shared_ptr<ConceptInteractTable> table);
	
		//���û���ҵ����򷵻�-1.
		int _MINDELEMENTINOUT IndexOf(const vector<shared_ptr<Concept>>& concepts,const shared_ptr<Concept> concept);

		bool IsSameConcept(const shared_ptr<Concept> left,const shared_ptr<Concept> right);

		void _MINDELEMENTINOUT WriteConcepts(const vector<shared_ptr<Concept>>& vec,ofstream& out);

		class _MINDELEMENTINOUT SameConcept
		{
			shared_ptr<Concept> _me;
		public:
			SameConcept(const shared_ptr<Concept> val):_me(val){}
			~SameConcept(){}

			bool operator()(const shared_ptr<Concept> val);
		};
	}
}


