#pragma once
#include "InOut.h"


namespace CommonTool
{
	///IterationDiverge represents divergence in an iteration process(for, while...)
	class _COMMONTOOLSINOUT IterationDiverge : public runtime_error
	{
	public:
		IterationDiverge();
		~IterationDiverge();

	private:

	};

	
}

