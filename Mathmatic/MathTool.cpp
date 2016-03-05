#include "StdAfx.h"
#include "MathTool.h"
#include "Vector.h"
#include "iMatrix.h"
#include "Rand.h"

#include <numeric>

namespace Math
{
	int DoubleCompare( double left,double right,double tol/*=1e-6*/ )
	{
		if(left<=right+tol&&left>=right-tol)
			return 0;
		else if(left>right+tol)
			return 1;
		else 
			return -1;
	}

	vector<double> _MATHMATICINOUT Normalized( const vector<double> val )
	{
		class Norm
		{
			double _sum;
		public:
			Norm(double sum):_sum(sum){}
			~Norm(){}

			double operator()(const double val)
			{
				return val/_sum;
			}
		};

		double sum=accumulate(val.begin(),val.end(),0.);
		vector<double> res(val.size());
		transform(val.begin(),val.end(),res.begin(),Norm(sum));

		return res;
	}

	vector<int> _MATHMATICINOUT GetDicemalDigit( const double val ,const int num)
	{
		vector<int> res;
		double decimal=val-(int)val;

		for (int i=0;i<=num;++i)
		{
			decimal=decimal*10;
			res.push_back((int)decimal);
			decimal=decimal-(int)decimal;
		}

		return res;
	}

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

	Vector ToVector( const double val[], const int n )
	{
		Vector vec(Tovector(val,n));
		return vec;
	}

	Math::Matrix CreateRandomMatrix(unsigned  int i,unsigned int j )
	{	
		vector<Vector> mat;
		for (unsigned int n=0;n<j;++n)
		{
			Vector vec(i);
			for (unsigned int m=0;m<i;++m)
			{
				double val=Rand::GetRandDecimal();
				vec.Set_ithVal(m,val);
			}
			vec=vec.Normalized();
			mat.push_back(vec);
		}

		return Matrix(mat);
	}

	double _MATHMATICINOUT ComputeDeviation( const vector<double>& vec1,const vector<double>& vec2 )
	{
		Check(vec1.size()==vec2.size());

		double sqSum=0.;
		for (unsigned int i=0;i<vec2.size();++i)
		{
			sqSum+=pow(vec1[i]-vec2[i],2);
		}

		return sqrt(sqSum/vec1.size());
	}

	bool _MATHMATICINOUT SameVec( const vector<double>& vec1,const vector<double>& vec2 )
	{
		if(vec1.size()!=vec2.size()) return false;

		for (unsigned int i=0;i<vec1.size();++i)
		{
			if(DoubleCompare(vec1[i],vec2[i])!=0)
			{
				return false;
			}
		}

		return true;
	}

	Matrix _MATHMATICINOUT ComputeMeanMatrix( const vector<Matrix>& mats )
	{
		Check(!mats.empty());

		Matrix sum(mats[0].Rows(),mats[0].Columns());
		for (unsigned int i=0;i<mats.size();++i)
		{
			sum+=mats[i];
		}

		return sum/mats.size();
	}

	Vector _MATHMATICINOUT ComputeMeanVector( const vector<Vector>& vecs )
	{
		Check(!vecs.empty());

		Vector sum(vecs[0].Dimension());
		for (unsigned int i=0;i<vecs.size();++i)
		{
			sum+=vecs[i];
		}

		return sum/vecs.size();
	}

	vector<Matrix> _MATHMATICINOUT ComputeNegateMatrix( const vector<Matrix>& mats )
	{
		vector<Matrix> res;
		res.reserve(mats.size());

		for (unsigned int i=0;i<mats.size();++i)
		{
			res.push_back(mats[i].Negate());
		}

		return res;
	}

	vector<Vector> _MATHMATICINOUT ComputeNegateVector( const vector<Vector>& vecs )
	{
		vector<Vector> res;
		res.reserve(vecs.size());

		for (unsigned int i=0;i<vecs.size();++i)
		{
			res.push_back(vecs[i].Negate());
		}

		return res;
	}

}

