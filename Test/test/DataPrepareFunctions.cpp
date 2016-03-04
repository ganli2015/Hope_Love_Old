#include "stdafx.h"
#include "DataPrepareFunctions.h"
#include "Vector.h"
#include "DataArray.h"
#include "iMatrix.h"
#include <stdlib.h>
#include <time.h> 
#include <math.h>


using namespace Math;
using namespace NeuralNetwork;
using namespace std;
vector<double> GenerateContinuousNumber( int from,int to )
{
	vector<double> res;
	for (int i=from;i<=to;++i)
	{
		res.push_back(i);
	}
	return res;
}

vector<double> Tovector( const double* val , const int n)
{
	int size=n;
	vector<double> vec;
	vec.reserve(size);
	for (int i=0;i<size;++i)
	{
		vec.push_back(val[i]);
	}
	assert(vec.size()==n);
	return vec;
}

vector<int> Tovector( const int val[], const int n )
{
	int size=n;
	vector<int> vec;
	vec.reserve(size);
	for (int i=0;i<size;++i)
	{
		vec.push_back(val[i]);
	}
	assert(vec.size()==n);
	return vec;
}

Vector ToVector( const double val[], const int n )
{
	Vector vec(Tovector(val,n));
	return vec;
}

shared_ptr<NeuralNetwork::iDataArray> ToDataArray( const double val[], const int n )
{
	return shared_ptr<DataArray>(new DataArray(Tovector(val,n)));
}

Math::Matrix CreateRandomMatrix( int i,int j )
{	
	vector<Vector> mat;
	for (unsigned int n=0;n<j;++n)
	{
		Vector vec(i);
		for (unsigned int m=0;m<i;++m)
		{
			double val=RandomDouble();
			vec.Set_ithVal(m,val);
		}
		vec=vec.Normalized();
		mat.push_back(vec);
	}
	
	return Matrix(mat);
}

double RandomDouble( int figure/*=10*/ )
{
	double val(0);
	for (int i=1;i<=figure;++i)
	{
		int r=rand()%10001;
		srand(r);
		double ran=(rand() % (10));
		val+=ran/pow(10.0,i);
	}
	return val;
}
