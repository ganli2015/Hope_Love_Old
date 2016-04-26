#pragma once
#include "InOut.h"

namespace Mind
{
	class iConcept;
	class BaseConcept;

	//��ʾĳ��Concept����BaseConcept֮��ľ���
	class _MINDELEMENTINOUT ConceptLevelTable
	{
	private:
		struct LevelInfo
		{
			shared_ptr<iConcept> base;
			int level;
		};

		shared_ptr<iConcept> _myConcept;
		vector<LevelInfo> _levels;
	public:
		ConceptLevelTable(const shared_ptr<iConcept> val);
		~ConceptLevelTable(void);

		//���_levelsû��concept�������һ����������֮ǰ��¼��concept��level���Ƚϣ�ѡ���С��level��
		void Insert(const shared_ptr<iConcept> concept,const int level);
		//<me>��concept֮���level�������ͬһ��concept������0.�������û�����ӹ�ϵ������-1.
		int LevelTo(const shared_ptr<iConcept> concept) const;
	private:
		int FindLevelInfoIndex(const shared_ptr<iConcept> concept) const;
	};
}


