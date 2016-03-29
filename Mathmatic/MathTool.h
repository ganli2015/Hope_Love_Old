#pragma once
#include "InOut.h"

namespace Math
{
	class Vector;
	class Matrix;

	const double PI=3.1415926;
	const double e=2.718281828459;
	const int BigInt=100000000;
	int _MATHMATICINOUT DoubleCompare(double left,double right,double tol=1e-6);
	vector<double> _MATHMATICINOUT Normalized(const vector<double> val);
	//获得val的小数部分的数字
	vector<int> _MATHMATICINOUT GetDicemalDigit(const double val,const int num);
	
	vector<double> _MATHMATICINOUT GenerateContinuousNumber(int from,int to);

	vector<double> _MATHMATICINOUT Tovector(const double val[], const int n);

	vector<int> _MATHMATICINOUT Tovector(const int val[], const int n);

	double _MATHMATICINOUT RandomDouble(int figure=10);

	Vector _MATHMATICINOUT ToVector(const double val[], const int n);

	Matrix _MATHMATICINOUT CreateRandomMatrix(unsigned int i,unsigned int j);

	double _MATHMATICINOUT ComputeDeviation(const vector<double>& vec1,const vector<double>& vec2);

	bool _MATHMATICINOUT SameVec(const vector<double>& vec1,const vector<double>& vec2);

	Matrix _MATHMATICINOUT ComputeMeanMatrix(const vector<Matrix>& mats);

	Vector _MATHMATICINOUT ComputeMeanVector(const vector<Vector>& vecs);

	vector<Matrix> _MATHMATICINOUT ComputeNegateMatrix(const vector<Matrix>& mats);

	vector<Vector> _MATHMATICINOUT ComputeNegateVector(const vector<Vector>& vecs);

	double _MATHMATICINOUT Round(const double& val);

	void _MATHMATICINOUT Reverse(vector<Math::Matrix>& mats);

	void _MATHMATICINOUT Reverse(vector<Math::Vector>& vecs);

	template<class T>
	double MeanValue(const vector<T>& vec)
	{
		double res=0;
		for (unsigned int i=0;i<vec.size();++i)
		{
			res+=vec[i];
		}

		return res/vec.size();
	}
}
