#include "StdAfx.h"
#include "CommonCompareFunction.h"
#include "../Mathmatic/MathTool.h"


namespace CommonTool
{


	bool comp_samedouble::operator()( const double val ) const
	{
		if(Math::DoubleCompare(val,_val)==0)
			return true;
		else return false;
	}

}