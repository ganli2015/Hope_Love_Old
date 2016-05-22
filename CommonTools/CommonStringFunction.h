#pragma once
#include "InOut.h"
#include <sstream>

namespace CommonTool
{
	//����<splitTag>�ָ��ַ���<str>
	_COMMONTOOLSINOUT vector<string> SplitString(const string& str, const char splitTag);

	//Convert to string.
	template<class T>
	string ToString(const T t)
	{
		stringstream ss;
		ss<<t;
		return ss.str();
	}

	_COMMONTOOLSINOUT int StrToInt(const string str);
}

