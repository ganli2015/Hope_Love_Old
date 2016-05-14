#pragma once
#include "InOut.h"

namespace Mind
{
	class iConcept;

	//表示某个Concept与其BaseConcept之间的距离
	class _MINDINTERFACEINOUT iConceptLevelTable: public MyObject
	{
	public:
		iConceptLevelTable(void);
		virtual ~iConceptLevelTable(void);

		//如果_levels没有concept，则添加一个；否则与之前记录的concept的level作比较，选择较小的level。
		virtual void Insert(const shared_ptr<iConcept> concept,const int level) =0;
		//<me>与concept之间的level，如果是同一个concept，返回0.如果两者没有连接关系，返回-1.
		virtual int LevelTo(const shared_ptr<iConcept> concept) const =0;
	};
}


