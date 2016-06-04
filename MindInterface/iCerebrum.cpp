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

	void iCerebrum::KillInstance()
	{
		delete _instance;
		_instance=NULL;
	}

	bool iCerebrum::Empty()
	{
		if(_instance==NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

}

