#include "StdAfx.h"
#include "CommonStringFunction.h"




vector<string> CommonTool::SplitString( const string& str, const char splitTag )
{
	vector<string> res;
	int startIndex=0;
	size_t found=str.find_first_of(splitTag,startIndex);//查找分割点的序号
	while(found!=string::npos)
	{
		res.push_back(string(str.begin()+startIndex,str.begin()+found));
		startIndex=found+1;//更新下个起点
		found=str.find_first_of(splitTag,startIndex);
	}
	res.push_back(string(str.begin()+startIndex,str.end()));//弹入最后一段

	return res;
}
