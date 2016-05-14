#pragma once
#include "InOut.h"

namespace Mind
{
	class iConcept;

	//��ʾĳ��Concept����BaseConcept֮��ľ���
	class _MINDINTERFACEINOUT iConceptLevelTable: public MyObject
	{
	public:
		iConceptLevelTable(void);
		virtual ~iConceptLevelTable(void);

		//���_levelsû��concept�������һ����������֮ǰ��¼��concept��level���Ƚϣ�ѡ���С��level��
		virtual void Insert(const shared_ptr<iConcept> concept,const int level) =0;
		//<me>��concept֮���level�������ͬһ��concept������0.�������û�����ӹ�ϵ������-1.
		virtual int LevelTo(const shared_ptr<iConcept> concept) const =0;
	};
}


