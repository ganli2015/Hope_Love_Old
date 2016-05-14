#include "StdAfx.h"
#include "CommonCompareFunction.h"
#include "../Mathmatic/MathTool.h"


namespace CommonTool
{


	bool comp_samedouble::operator()( const double val ) const
	{
		if(DoubleCompare(val,_val)==0)
			return true;
		else return false;
	}

	int comp_samedouble::DoubleCompare( double left,double right,double tol/*=1e-6*/ ) const 
	{
		if(left<=right+tol&&left>=right-tol)
			return 0;
		else if(left>right+tol)
			return 1;
		else 
			return -1;
	}

}