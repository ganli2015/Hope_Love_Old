#include "StdAfx.h"
#include "CommonStringFunction.h"

#include "GeneralFunctor.h"


namespace CommonTool
{
	vector<string> SplitString( const string& str, const char splitTag )
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

	_COMMONTOOLSINOUT int StrToInt( const string str )
	{
		stringstream ss(str);
		int res;
		ss>>res;
		return res;
	}

	_COMMONTOOLSINOUT void TrimBeginEndBlank( string& str )
	{
		CREATE_FUNCTOR_O(AppendNonBlank,char,string,
			if(input!=' ')
			{
				_output.push_back(input);
			}
		);

		AppendNonBlank app;
		app=for_each(str.begin(),str.end(),app);

		str=app.GetResult();
	}
}

