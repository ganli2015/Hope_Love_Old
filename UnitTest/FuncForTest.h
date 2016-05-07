#pragma once
#include "PublicHeader.h"

namespace Mind
{
	class iConcept;
}

namespace FuncForTest
{
	shared_ptr<Mind::iConcept> SimpleConcept(const string str);

	template<class T>
	bool ContainSameElements(const vector<vector<T>>& v1,const vector<vector<T>>& v2)
	{
		if(v1.size()!=v2.size()) return false;

		vector<vector<T>> v2Copy=v2;
		for (unsigned int i=0;i<v1.size();++i)
		{
			bool exist=false;
			int existIndex=-1;
			for (unsigned int j=0;j<v2Copy.size();++j)
			{
				if(ContainSameElements(v1[i],v2Copy[j]))
				{
					exist=true;
					existIndex=j;
					break;
				}
			}

			if(!exist)
			{
				return false;
			}
			else
			{
				v2Copy.erase(v2Copy.begin()+existIndex);
			}
		}

		return true;
	}

	template<class T>
	bool ContainSameElements(const vector<T>& v1,const vector<T>& v2)
	{
		if(v1.size()!=v2.size())
		{
			return false;
		}

		for (unsigned int i=0;i<v1.size();++i)
		{
			if(v1[i]!=v2[i])
			{
				return false;
			}
		}

		return true;
	}
}

