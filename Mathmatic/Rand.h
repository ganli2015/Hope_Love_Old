#pragma once
#include "InOut.h"
#include <random>

namespace Math
{
	class _MATHMATICINOUT Rand
	{
		static random_device _rd;
	public:
		Rand(void);
		~Rand(void);

		 static int GetRandInt(const int start,const int end);
		 //得到有权重的自然数，自然数范围从0到<weights.size()-1>，每个自然数的权重就对应于<weights>的元素。
		 static int GetRandInt(const vector<double>& weights);

		 static double GetRandDouble(const double min,const double max);
		 //返回0到1的小数。
		 static double GetRandDecimal();
		 //true的概率为p。
		 static bool RandTrue(const double p);
	};
}


