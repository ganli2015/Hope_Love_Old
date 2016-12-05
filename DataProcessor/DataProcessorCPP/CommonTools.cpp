#include "stdafx.h"
#include "CommonTools.h"


CommonTools::CommonTools()
{
}


CommonTools::~CommonTools()
{
}

vector<string> CommonTools::SplitString(const string& str, const char splitTag)
{
	vector<string> res;
	int startIndex = 0;
	size_t found = str.find_first_of(splitTag, startIndex);//���ҷָ������
	while (found != string::npos)
	{
		res.push_back(string(str.begin() + startIndex, str.begin() + found));
		startIndex = found + 1;//�����¸����
		found = str.find_first_of(splitTag, startIndex);
	}
	res.push_back(string(str.begin() + startIndex, str.end()));//�������һ��

	return res;
}
