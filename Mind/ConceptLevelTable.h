#pragma once
#include "InOut.h"

namespace Mind
{
	class Concept;
	class BaseConcept;

	//��ʾĳ��Concept����BaseConcept֮��ľ���
	class _MINDINOUT ConceptLevelTable
	{
	private:
		struct LevelInfo
		{
			shared_ptr<Concept> base;
			int level;
		};

		shared_ptr<Concept> _myConcept;
		vector<LevelInfo> _levels;
	public:
		ConceptLevelTable(const shared_ptr<Concept> val);
		~ConceptLevelTable(void);

		//���_levelsû��concept�������һ����������֮ǰ��¼��concept��level���Ƚϣ�ѡ���С��level��
		void Insert(const shared_ptr<Concept> concept,const int level);
		//<me>��concept֮���level�������ͬһ��concept������0.�������û�����ӹ�ϵ������-1.
		int LevelTo(const shared_ptr<Concept> concept) const;
	private:
		int FindLevelInfoIndex(const shared_ptr<Concept> concept) const;
	};
}


