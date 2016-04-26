#include "StdAfx.h"
#include "ConceptLevelTable.h"
#include "../MindInterface/iConcept.h"


namespace Mind
{
	ConceptLevelTable::ConceptLevelTable(const shared_ptr<iConcept> val):_myConcept(val)
	{
	}


	ConceptLevelTable::~ConceptLevelTable(void)
	{
	}

	void ConceptLevelTable::Insert( const shared_ptr<iConcept> concept,const int level )
	{
		Check(concept->IsBaseConcept());
		int findLevelIndex=FindLevelInfoIndex(concept);
		if(findLevelIndex>=0)//如果已经存在concept
		{
			LevelInfo info=_levels[findLevelIndex];
			if(level<info.level)
			{
				info.level=level;
				_levels[findLevelIndex]=info;
			}
		}
		else
		{
			LevelInfo info;
			info.base=concept;
			info.level=level;
			_levels.push_back(info);
		}
	}

	int ConceptLevelTable::FindLevelInfoIndex( const shared_ptr<iConcept> concept ) const
	{
		class SameConcept
		{
			shared_ptr<iConcept> _val;
		public:
			SameConcept(shared_ptr<iConcept> val):_val(val){}
			~SameConcept(){}

			bool operator()(const LevelInfo info)
			{
				if(info.base->Same(_val))
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		};

		vector<LevelInfo>::const_iterator it=find_if(_levels.begin(),_levels.end(),SameConcept(concept));
		if(it!=_levels.end())
		{
			return distance(_levels.begin(),it);
		}
		else
		{
			return -1;
		}
		
	}

	int ConceptLevelTable::LevelTo( const shared_ptr<iConcept> concept ) const
	{
		int findLevelIndex=FindLevelInfoIndex(concept);
		if(findLevelIndex<0)
		{
			return -1;
		}
		else
		{
			return _levels[findLevelIndex].level;
		}

	}

}

