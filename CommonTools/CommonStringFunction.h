#pragma once
#include "InOut.h"
#include <sstream>

namespace CommonTool
{
	//°´ÕÕ<splitTag>·Ö¸î×Ö·û´®<str>
	_COMMONTOOLSINOUT vector<string> SplitString(const string& str, const char splitTag);

	template<class T>
	string ToString(const T t)
	{
		stringstream ss;
		ss<<t;
		return ss.str();
	}
}

