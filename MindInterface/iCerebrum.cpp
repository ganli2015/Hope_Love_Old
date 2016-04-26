#include "Stdafx.h"
#include "iCerebrum.h"

namespace Mind
{

	iCerebrum* iCerebrum::_instance;


	iCerebrum* iCerebrum::Instance()
	{
		return _instance;
	}

	void iCerebrum::SetInstance( iCerebrum* val )
	{
		_instance=val;
	}
}

