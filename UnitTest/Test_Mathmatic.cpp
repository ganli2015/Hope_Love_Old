#include "StdAfx.h"
#include "Test_Mathmatic.h"

#include "../Mathmatic/Rand.h"
#include "../Mathmatic/FindSequence.h"
#include "../Mathmatic/Vector.h"
#include "../Mathmatic/iMatrix.h"
#include "../Mathmatic/MyInt.h"

#include <windows.h>
#include <iterator>
#include <iostream>

using namespace Math;

Test_Mathmatic::Test_Mathmatic(void)
{
}


Test_Mathmatic::~Test_Mathmatic(void)
{
}

void Test_Mathmatic::RunTest()
{
	TestMatrix();
	TestSubSequence();
	TestRand();
	TestMyInt();
}

void Test_Mathmatic::TestRand()
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
		}

		cout<<"weights: ";
		copy(weights.begin(),weights.end(),ostream_iterator<double>(cout," "));
		cout<<endl;
		copy(counts.begin(),counts.end(),ostream_iterator<int>(cout," "));
		cout<<endl;

		Check(DoubleCompare((double)counts[1]/counts[0],1.5,0.15)==0);
	}

	{
		vector<double> weights;
		weights.push_back(0.3);
		weights.push_back(0.7);

		vector<int> counts(weights.size());
		for (unsigned int i=0;i<10000;++i)
		{
			counts[Math::Rand::GetRandInt(weights)]++;
		}

		cout<<"weights: ";
		copy(weights.begin(),weights.end(),ostream_iterator<double>(cout," "));
		cout<<endl;
		copy(counts.begin(),counts.end(),ostream_iterator<int>(cout," "));
		cout<<endl;

		Check(DoubleCompare((double)counts[1]/counts[0],7./3.,7./30)==0);
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
		}

		cout<<"weights: ";
		copy(weights.begin(),weights.end(),ostream_iterator<double>(cout," "));
		cout<<endl;
		copy(counts.begin(),counts.end(),ostream_iterator<int>(cout," "));
		cout<<endl;

		Check(DoubleCompare((double)counts[1]/counts[0],5.,0.5)==0);
		Check(DoubleCompare((double)counts[2]/counts[1],0.8,0.08)==0);
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

		Check(DoubleCompare((double)counts[1]/counts[0],7./4.,7./40)==0);
		Check(DoubleCompare((double)counts[2]/counts[1],1./7.,1./70)==0);
	}
}


void Test_Mathmatic::TestMyInt()
{
	{
		MyInt init(80);
		init+=300;
		int newIntInt=init.GetInt();
		Check(newIntInt==380);
	}

	{
		MyInt init(999999999);
		init+=300;
		int newIntInt=init.GetInt();
		Check(newIntInt==300+999999999);
	}
}

void Test_Mathmatic::TestMatrix()
{
	{
		Matrix mat1(5,1);
		mat1.SetElem(0,0,0.7323708843546246);
		mat1.SetElem(1,0,0.8238067985141946);
		mat1.SetElem(2,0,7.955921894817479);
		mat1.SetElem(3,0,4.550095218027913);
		mat1.SetElem(4,0,9.080872417835938);
		Matrix mat2(1,5);
		mat2.SetElem(0,0,4.526692059955423);
		mat2.SetElem(0,1,8.978426943671558);
		mat2.SetElem(0,2,0.42316040787398634);
		mat2.SetElem(0,3,0.33500171321514394);
		mat2.SetElem(0,4,6.948578240728466);

		Matrix res=mat1*mat2;
		Matrix expect(5,5);
		double r1[]={3.3152174671506103,6.575538480850128,0.309910362138535,0.2453455009676893,5.088936391169608};
		double r2[]={3.7291196937715014,7.39648915615965,0.34860242086862947,0.27597668886053806,5.724285994719912};
		double r3[]={36.01400847089578,71.43166350217572,3.366631154024543,2.6652474649697298,55.28234576326392};
		double r4[]={20.59687989548809,40.852697501812926,1.9254201483261664,1.5242896933313848,31.6166926252314};
		double r5[]={41.10631307128614,81.53194958834206,3.842665676183088,3.0421078174631857,63.099152489406094};
		expect.Set_ithRow(0,r1,5);
		expect.Set_ithRow(1,r2,5);
		expect.Set_ithRow(2,r3,5);
		expect.Set_ithRow(3,r4,5);
		expect.Set_ithRow(4,r5,5);

		Check(res.Same(expect));
	}

	{
		Matrix mat1(3,3);
		double m1r1[]={4.7103874272019315,9.224960690976026,2.9770739431793185};
		double m1r2[]={4.5689512324933865,1.594954462671005,6.487427713943966};
		double m1r3[]={8.77367474666378,2.5215923836107343,3.4504870727758785};
		int rowLength=3;
		mat1.Set_ithRow(0,m1r1,rowLength);
		mat1.Set_ithRow(1,m1r2,rowLength);
		mat1.Set_ithRow(2,m1r3,rowLength);
		Matrix mat2(3,3);
		double m2r1[]={7.68834049999208,9.786212729098139,7.1890853835146835};
		double m2r2[]={9.918345284449558,3.8036926403553295,0.508702279691919};
		double m2r3[]={1.5249721898869613,3.2581674892440855,8.261607168833603};
		mat2.Set_ithRow(0,m2r1,rowLength);
		mat2.Set_ithRow(1,m2r2,rowLength);
		mat2.Set_ithRow(2,m2r3,rowLength);

		Matrix res=mat1*mat2;
		Matrix expect(3,3);
		double r1[]={132.25136276637028,90.88557402164265,63.15155136827457};
		double r2[]={60.84010872467886,71.9165713278123,87.25451680348439};
		double r3[]={97.72691964337001,106.69467468085953,92.8640054113619};
		expect.Set_ithRow(0,r1,rowLength);
		expect.Set_ithRow(1,r2,rowLength);
		expect.Set_ithRow(2,r3,rowLength);

		Check(res.Same(expect));
	}

	{
		Matrix mat1(2,3);
		double m1r1[]={1.1764746567695532,0.28443348963539705,2.024309156544499};
		double m1r2[]={9.355947107653918,1.2518149299294237,3.236974794275678};
		int rowLength=3;
		mat1.Set_ithRow(0,m1r1,rowLength);
		mat1.Set_ithRow(1,m1r2,rowLength);
		Matrix mat2(3,4);
		double m2r1[]={2.232941725941055,3.6512944582113214,9.38670588996261,0.8068821322763604};
		double m2r2[]={1.675232276612796,9.274778498405574,1.7526312819937857,0.2499133367785067};
		double m2r3[]={7.77941716444348,0.02458644391077769,4.083880800684863,4.387769727928969};
		rowLength=4;
		mat2.Set_ithRow(0,m2r1,rowLength);
		mat2.Set_ithRow(1,m2r2,rowLength);
		mat2.Set_ithRow(2,m2r3,rowLength);

		Matrix res=mat1*mat2;
		Matrix expect(2,4);
		double r1[]={18.85143691156212,6.983483571921036,19.808765920734807,9.902562539165029};
		double r2[]={48.17014273280063,45.851209720807546,103.23491304169812,22.065091810248376};
		expect.Set_ithRow(0,r1,rowLength);
		expect.Set_ithRow(1,r2,rowLength);

		Check(res.Same(expect));
	}
}

void Test_Mathmatic::TestSubSequence()
{
	{
		int a[9]={1,2,6,3,7,8,9,3,2};
		int b[7]={2,9,5,3,3,8,3};
		vector<int> avec=Tovector(a,9);
		vector<int> bvec=Tovector(b,7);
		vector<int> lcs;
		FindLongestCommonSubsequence(avec,bvec,lcs);

		vector<int> expect;
		expect.push_back(2);
		expect.push_back(3);
		expect.push_back(8);
		expect.push_back(3);
		Check(SameVec(lcs,expect));
	}

	{
		int a[10]={7,8,9,0,9,7,1,0,3,7};
		int b[20]={6,8,7,7,3,8,9,7,1,0,5,9,7,3,0,0,0,9,5,2};
		vector<int> avec=Tovector(a,10);
		vector<int> bvec=Tovector(b,20);
		vector<int> lcs;
		FindLongestCommonSubsequence(avec,bvec,lcs);

		int c[7]={7,8,9,0,9,7,0};
		vector<int> expect=Tovector(c,7);
		Check(SameVec(lcs,expect));
	}

}

