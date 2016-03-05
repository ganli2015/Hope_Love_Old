#pragma once
#include "InOut.h"
#include <sstream>

namespace CommonTool
{
	//����<splitTag>�ָ��ַ���<str>
	_COMMONTOOLSINOUT vector<string> SplitString(const string& str, const char splitTag);

	template<class T>
	string ToString(const T t)
	{
		stringstream ss;
		ss<<t;
		return ss.str();
	}
}

