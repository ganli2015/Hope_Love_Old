#pragma once
#include "InOut.h"

namespace CommonTool
{
	template<class T>
	void DeleteVectorPtr(std::vector<T*>& vec)
	{
		for (unsigned int i=0;i<vec.size();++i)
		{
			delete vec[i];
		}
		std::vector<T*>().swap(vec);
	}
}


