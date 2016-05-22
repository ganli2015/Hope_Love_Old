#include "StdAfx.h"
#include "CommonStringFunction.h"




vector<string> CommonTool::SplitString( const string& str, const char splitTag )
{
	vector<string> res;
	int startIndex=0;
	size_t found=str.find_first_of(splitTag,startIndex);//���ҷָ������
	while(found!=string::npos)
	{
		res.push_back(string(str.begin()+startIndex,str.begin()+found));
		startIndex=found+1;//�����¸����
		found=str.find_first_of(splitTag,startIndex);
	}
	res.push_back(string(str.begin()+startIndex,str.end()));//�������һ��

	return res;
}

_COMMONTOOLSINOUT int CommonTool::StrToInt( const string str )
{
	stringstream ss(str);
	int res;
	ss>>res;
	return res;
}
