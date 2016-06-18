#include "StdAfx.h"
#include "Rand.h"
#include "MathTool.h"

#include <time.h>
#include <numeric>

namespace Math
{
	random_device Rand::_rd;

	Rand::Rand(void)
	{
	}


	Rand::~Rand(void)
	{
	}

	int Rand::GetRandInt( const int start,const int end )
	{
		uniform_int_distribution<int> dis(start,end);

		return dis(_rd);
	}

	int Rand::GetRandInt( const vector<double>& weights )
	{
		////把最小的元素归一化，然后其他元素放大或缩小相同比例，并且都变成int类型。
		//double minWeight=*min_element(weights.begin(),weights.end());
		//double normFactor=1./minWeight;

		//class Norm
		//{
		//	double _factor;
		//public:
		//	Norm(const double val):_factor(val){}
		//	~Norm(){}

		//	int operator()(const double weight)
		//	{
		//		return (int)(weight*_factor);
		//	}
		//};

		//vector<int> int_weights(weights.size());
		//transform(weights.begin(),weights.end(),int_weights.begin(),Norm(normFactor));

		////计算int值总和，把{1,randIndex}作为随机的总区间
		//int totalInt=accumulate(int_weights.begin(),int_weights.end(),0);
		//int randIndex=GetRandInt(1,totalInt);

		////找到randIndex对应哪个权重值
		//int searchIndex=0;
		//for (unsigned int i=0;i<int_weights.size();++i)
		//{
		//	searchIndex+=int_weights[i];
		//	if(randIndex<=searchIndex)
		//	{
		//		return i;
		//	}
		//}

		//throw runtime_error("Error in GetRandInt!");

		vector<double> normed=Normalized(weights);
		double randDouble=GetRandDecimal();

		//找到randDouble对应哪个权重值
		double searchIndex=0;
		for (unsigned int i=0;i<normed.size();++i)
		{
			searchIndex+=normed[i];
			if(randDouble<=searchIndex)
			{
				return i;
			}
		}

		throw runtime_error("Error in GetRandInt!");
	}

	double Rand::GetRandDouble(const double min,const double max)
	{
		uniform_real_distribution<double> dis(min,max);

		return dis(_rd);
	}

	double Rand::GetRandDecimal()
	{
		uniform_real_distribution<double> dis(0,1);

		return dis(_rd);
	}

	bool Rand::RandTrue( const double p )
	{
		double val=GetRandDecimal();
		if(val<=p)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

}

