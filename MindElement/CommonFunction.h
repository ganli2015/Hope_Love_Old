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

	class iConcept;
	class iConceptInteractTable;
	class iConceptChain;
	namespace CommonFunction
	{
		//��<from>��<to>�������໥���ö���ӵ�table
		void AppendToInteractTable(const vector<shared_ptr<iConcept>>& from,const vector<shared_ptr<iConcept>>& to,shared_ptr<iConceptInteractTable> table);
	
		//���û���ҵ����򷵻�-1.
		int _MINDELEMENTINOUT IndexOf(const vector<shared_ptr<iConcept>>& concepts,const shared_ptr<iConcept> concept);

		bool IsSameConcept(const shared_ptr<iConcept> left,const shared_ptr<iConcept> right);

		void _MINDELEMENTINOUT WriteConcepts(const vector<shared_ptr<iConcept>>& vec,ofstream& out);

		class _MINDELEMENTINOUT SameConcept
		{
			shared_ptr<iConcept> _me;
		public:
			SameConcept(const shared_ptr<iConcept> val):_me(val){}
			~SameConcept(){}

			bool operator()(const shared_ptr<iConcept> val);
		};
	}
}


