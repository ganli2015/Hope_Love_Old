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
		 //�õ���Ȩ�ص���Ȼ������Ȼ����Χ��0��<weights.size()-1>��ÿ����Ȼ����Ȩ�ؾͶ�Ӧ��<weights>��Ԫ�ء�
		 static int GetRandInt(const vector<double>& weights);

		 static double GetRandDouble(const double min,const double max);
		 //����0��1��С����
		 static double GetRandDecimal();
		 //true�ĸ���Ϊp��
		 static bool RandTrue(const double p);
	};
}


