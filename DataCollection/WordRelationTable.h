#pragma once
#include "InOut.h"
#include <map>

namespace DataCollection
{
	class Word;
	class _DATACOLLECTIONINOUT WordRelationTable
	{
		vector<shared_ptr<Word>> _words;
		multimap<int,int> _relationIndex;

	public:
		WordRelationTable(void);
		~WordRelationTable(void);

		void Add(const shared_ptr<Word> from, const shared_ptr<Word> to);
	};
}


