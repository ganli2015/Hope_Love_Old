#pragma once
#include "InOut.h"

namespace CommonTool
{
	_COMMONTOOLSINOUT std::vector<std::string> InputStringFromFile(std::string filename);

	template<class T>
	void ConcoleDisplay(const vector<T>& vec)
	{
		for (unsigned int i=0;i<vec.size();++i)
		{
			cout<<vec[i]<<" ";
		}
		cout<<endl;
	}
}

