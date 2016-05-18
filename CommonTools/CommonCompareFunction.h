#pragma once
#include "InOut.h"

//#include "MyObject.h"

namespace CommonTool
{
	//compare two pointers
	template <class T>
	class comp_ptr
	{
		shared_ptr<T> _test_ptr;
	public:
		comp_ptr(shared_ptr<T> test_ptr):_test_ptr(test_ptr){}
		~comp_ptr(){}
		bool operator()(const shared_ptr<T> val) const
		{
			if(*val==*_test_ptr)
				return true;
			else return false;
		}
	};

	//compare two doubles
	class _COMMONTOOLSINOUT comp_samedouble
	{
		double _val;
	public:
		comp_samedouble(const double val):_val(val){}
		~comp_samedouble(){}
		bool operator()(const double val) const;

		int DoubleCompare( double left,double right,double tol=1e-6 ) const;
	};
}
