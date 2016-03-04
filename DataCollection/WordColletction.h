#pragma once
#include "InOut.h"

namespace DataCollection
{
	class PrepositionCollection;
	class _DATACOLLECTIONINOUT WordColletction
	{
		std::tr1::shared_ptr<PrepositionCollection> _preposetionCollection;
	public:
		WordColletction(void);
		~WordColletction(void);
	};
}


