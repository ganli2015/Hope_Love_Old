#pragma once
#include "StdAfx.h"
#include "InOut.h"
#include "MathTool.h"

namespace Math
{
	using namespace std;

// 	class _MATHMATICINOUT iVector
// 	{
// 	public: 
// 		iVector(){}
// 		virtual ~iVector(){}
// 
// 		virtual unsigned int Dimension() const =0;
// 	};


	class _MATHMATICINOUT Vector
	{
		const unsigned int _d; //dimension,count from 1.
		std::vector<double> _r;
	public:
		Vector(const unsigned int d);

		~Vector(void);

		Vector(std::vector<double> r);

		Vector(const Vector& vec);

		Vector(const int d,const double val);

		const std::vector<double>& GetVector() const;

		unsigned int Dimension() const;

		double Norm() const;

		double Angle(const Vector& vec);

		bool IsOrthogonoality(const Vector& vec,double tol=1e-6);

		void Set_ithVal(unsigned int i,double val);
		double Get_ithVal(unsigned int i) const;

		double Dot(const Vector& val) const;

		Vector Normalized() const;

		void Normalize();

		bool Same(const Vector& v ,const double tol=1e-6) const ;

		double& operator[]( unsigned int i);

		const double operator[]( unsigned int i) const;

		Vector& operator=(const Vector& vec);

		Vector& operator+=(const Vector& right);

		_MATHMATICINOUT friend Vector operator/(const Vector& left,const double& right);
		
	};

	_MATHMATICINOUT Vector operator+(const Vector& left,const Vector& right) ;

	_MATHMATICINOUT Vector operator-(const Vector& left,const Vector& right);

	_MATHMATICINOUT Vector operator*(const Vector& left,const double val) ;

	_MATHMATICINOUT double operator*(const Vector& left,const Vector& right) ;

	_MATHMATICINOUT Vector operator*(const double val,const Vector& vec);
}


