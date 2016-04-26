#pragma once
#include "InOut.h"

namespace Mind
{
	class iConcept;
	class BaseConcept;

	//表示某个Concept与其BaseConcept之间的距离
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

		//如果_levels没有concept，则添加一个；否则与之前记录的concept的level作比较，选择较小的level。
		void Insert(const shared_ptr<iConcept> concept,const int level);
		//<me>与concept之间的level，如果是同一个concept，返回0.如果两者没有连接关系，返回-1.
		int LevelTo(const shared_ptr<iConcept> concept) const;
	private:
		int FindLevelInfoIndex(const shared_ptr<iConcept> concept) const;
	};
}


