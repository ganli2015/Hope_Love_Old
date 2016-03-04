#pragma once
#include "InOut.h"
#include "Word.h"
#include <map>

namespace DataCollection
{
	class _DATACOLLECTIONINOUT PrepositionCollection
	{
		std::map<long long,Word> _prepositions;

		void Initialize();
	public:
		PrepositionCollection(void);
		~PrepositionCollection(void);

	};

}

