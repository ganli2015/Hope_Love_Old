#pragma once
#include "PublicHeader.h"
#include <gmock/gmock.h>
#include "../Mathmatic/MathTool.h"


MATCHER_P(SameConceptTable,table,"")
{
	if(Math::DoubleCompare(arg->Similarity(table),1)==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}