#include "StdAfx.h"
#include "Vector.h"


namespace Math
{
	Math::Vector::Vector( const unsigned int d ) :_d(d),_r(_d)
	{

	}

	Math::Vector::Vector( std::vector<double> r ) :_d(r.size()),_r(r)
	{

	}

	Math::Vector::Vector( const int d,const double val ) :_d(d)
	{
		_r.reserve(d);
		for (int i=0;i<d;++i)
		{
			_r.push_back(val);
		}
	}


	Vector::Vector( const Vector& vec ) :_d(vec._d),_r(vec._r)
	{

	}


	Math::Vector::~Vector( void )
	{

	}

	const std::vector<double>& Math::Vector::GetVector() const
	{
		return _r;
	}

	unsigned int Math::Vector::Dimension() const
	{
		return _d;
	}

	double Math::Vector::Norm() const
	{
		return sqrt(this->Dot(*this));
	}

	double Math::Vector::Angle( const Vector& vec )
	{
		assert_same_int(_d,vec.Dimension());
		return acos(this->Dot(vec)/this->Norm()/vec.Norm());
	}

	bool Math::Vector::IsOrthogonoality( const Vector& vec,double tol/*=1e-6*/ )
	{
		assert_same_int(_d,vec.Dimension());
		if(DoubleCompare(this->Dot(vec),0)==0)
			return true;
		else return false;
	}

	void Math::Vector::Set_ithVal( unsigned int i,double val )
	{
		assert_less(i,_d);_r[i]=val;
	}

	double Math::Vector::Get_ithVal(unsigned int i ) const
	{
		assert_less(i,_d);return _r[i];
	}

	double Math::Vector::Dot( const Vector& val ) const
	{
		assert_same_int(_d,val.Dimension());
		double result(0);
		for (size_t i=0;i<Dimension();++i)
		{
			result+=_r[i]*val[i];
		}
		return result;
	}

	Vector& Math::Vector::operator=( const Vector& vec )
	{
		assert_same_int(_d,vec.Dimension());
		_r=vec._r;
		// 			_r.clear();
		// 			_r.reserve(_d);
		// 			for (size_t i=0;i<vec.Dimension();++i)
		// 			{
		// 				_r.push_back(vec[i]);
		// 			}
		return *this;
	}

	double& Vector::operator[](unsigned int i)
	{
		assert_less(i,_d);
		assert_less_equal(0,i);
		return _r.at(i);
	}

	Vector Vector::Normalized() const
	{
		vector<double> vec(_r);
		double norm=Norm();
		for (unsigned int i=0;i<vec.size();++i)
		{
			vec[i]/=norm;
		}
		return Vector(vec);
	}

	const double Vector::operator[](unsigned int i) const
	{
		assert_less(i,_d);
		assert_less_equal(0,i);
		return _r.at(i);
	}

	void Vector::Normalize()
	{
		double norm=Norm();
		for (unsigned int i=0;i<_d;++i)
		{
			_r[i]/=norm;
		}
	}

	bool Vector::Same( const Vector& v ,const double tol) const
	{
		if(v._d!=_d)
		{
			return false;
		}

		for (unsigned int i=0;i<_d;++i)
		{
			if(DoubleCompare(_r[i],v._r[i],tol)!=0)
			{
				return false;
			}
		}

		return true;
	}

	Vector& Vector::operator+=( const Vector& right )
	{
		Check(Dimension()==right.Dimension());

		for (unsigned int i=0;i<Dimension();++i)
		{
			_r[i]+=right.Get_ithVal(i);
		}

		return *this;
	}



	Vector operator+(const Vector& left,const Vector& right) 
	{
		assert_same_int(left.Dimension(),right.Dimension());
		int n=left.Dimension();
		vector<double> newvec;
		newvec.reserve(n);
		for (int i=0;i<n;++i)
		{
			newvec.push_back(left[i]+right[i]);
		}
		return Vector(newvec);
	}

	Vector operator-(const Vector& left,const Vector& right) 
	{
		assert_same_int(left.Dimension(),right.Dimension());
		int n=left.Dimension();
		vector<double> newvec;
		newvec.reserve(n);
		for (int i=0;i<n;++i)
		{
			newvec.push_back(left[i]-right[i]);
		}
		return Vector(newvec);
	}

	Vector operator*(const Vector& left,const double val) 
	{
		int n=left.Dimension();
		vector<double> newvec;
		newvec.reserve(n);
		for (int i=0;i<n;++i)
		{
			newvec.push_back(left[i]*val);
		}
		return Vector(newvec);
	}

	double operator*(const Vector& left,const Vector& right) 
	{
		assert_same_int(left.Dimension(),right.Dimension());
		int n=left.Dimension();
		return left.Dot(right);
	}

	Vector operator*(const double val,const Vector& vec)
	{
		return vec*val;
	}


	Vector operator/( const Vector& left,const double& right )
	{
		Check(DoubleCompare(right,0)!=0);

		Vector res(left);
		for (unsigned int i=0;i<res.Dimension();++i)
		{
			res.Set_ithVal(i,res.Get_ithVal(i)/right);
		}

		return res;
	}

}

