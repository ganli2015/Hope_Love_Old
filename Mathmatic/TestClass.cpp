#include "StdAfx.h"
#include "TestClass.h"
#include "Rand.h"
#include "FindSequence.h"
#include "Vector.h"
#include "iMatrix.h"
#include "MyInt.h"

#include <windows.h>
#include <iterator>
#include <iostream>

using namespace Math;

TestClass::TestClass(void)
{
}


TestClass::~TestClass(void)
{
}

void TestClass::TestRand()
{
	int count=0;
	for (unsigned int i=0;i<200;++i)
	{
		if(Math::Rand::RandTrue(0.77))
		{
			count++;
		}
	}
	double ratio=(double)count/200;

	{
		vector<double> weights;
		weights.push_back(0.4);
		weights.push_back(0.6);

		vector<int> counts(weights.size());
		for (unsigned int i=0;i<10000;++i)
		{
			counts[Math::Rand::GetRandInt(weights)]++;
			//Sleep(1);
		}

		cout<<"weights: ";
		copy(weights.begin(),weights.end(),ostream_iterator<double>(cout," "));
		cout<<endl;
		copy(counts.begin(),counts.end(),ostream_iterator<int>(cout," "));
		cout<<endl;
	}

	{
		vector<double> weights;
		weights.push_back(0.3);
		weights.push_back(0.7);

		vector<int> counts(weights.size());
		for (unsigned int i=0;i<10000;++i)
		{
			counts[Math::Rand::GetRandInt(weights)]++;
			//Sleep(1);
		}

		cout<<"weights: ";
		copy(weights.begin(),weights.end(),ostream_iterator<double>(cout," "));
		cout<<endl;
		copy(counts.begin(),counts.end(),ostream_iterator<int>(cout," "));
		cout<<endl;
	}

	{
		vector<double> weights;
		weights.push_back(0.1);
		weights.push_back(0.5);
		weights.push_back(0.4);

		vector<int> counts(weights.size());
		for (unsigned int i=0;i<10000;++i)
		{
			counts[Math::Rand::GetRandInt(weights)]++;
			//Sleep(1);
		}

		cout<<"weights: ";
		copy(weights.begin(),weights.end(),ostream_iterator<double>(cout," "));
		cout<<endl;
		copy(counts.begin(),counts.end(),ostream_iterator<int>(cout," "));
		cout<<endl;
	}

	{
		vector<double> weights;
		weights.push_back(40);
		weights.push_back(70);
		weights.push_back(10);

		vector<int> counts(weights.size());
		for (unsigned int i=0;i<10000;++i)
		{
			counts[Math::Rand::GetRandInt(weights)]++;
			//Sleep(1);
		}

		cout<<"weights: ";
		copy(weights.begin(),weights.end(),ostream_iterator<double>(cout," "));
		cout<<endl;
		copy(counts.begin(),counts.end(),ostream_iterator<int>(cout," "));
		cout<<endl;
	}
}

void TestClass::TestMath()
{
	Vector vec1(GenerateContinuousNumber(1,5));
	Vector vec2(GenerateContinuousNumber(2,6));
	Vector vec3(GenerateContinuousNumber(3,7));
	vector<Vector> matvec;
	matvec.push_back(vec1);
	matvec.push_back(vec2);
	matvec.push_back(vec3);

	Matrix mat(matvec);
	Vector leftvec(GenerateContinuousNumber(0,4));
	Vector rightvec(GenerateContinuousNumber(4,6));

	Vector leftMulti=leftvec*mat;
	Vector rightMulti=mat*rightvec;



	int a[9]={1,2,6,3,7,8,9,3,2};
	int b[7]={2,9,5,3,3,8,3};
	vector<int> avec=Tovector(a,9);
	vector<int> bvec=Tovector(b,7);
	vector<int> lcs;
	FindLongestCommonSubsequence(avec,bvec,lcs);
	vector<vector<int>> cs;
	FindAllCommonSubsequence(avec,bvec,cs);


	bool match=IsMatch("了的","的空间发生了的就分是了的金佛山");
	int matchCount=MatchCount("了的","的空间发生了的就分是了的金的请哦呜为IE青浦区的快捷方式佛山");
	int matchCount2=MatchCount("的金的请哦呜","的空间发生了的就分是了的金的请哦呜为IE青浦区的快捷方式佛山");
}

void TestClass::TestMyInt()
{
	MyInt init(80);
// 	for (int i=0;i<300;++i)
// 	{
// 		++init;
// 		cout<<init.GetDouble()<<" "<<init.GetInt()<<endl;
// 	}

//	MyInt newInt=init+300;
	init+=300;
	int newIntInt=init.GetInt();
}
