#pragma once
#include <gcroot.h>
#include "InOut.h"
using namespace Interactor;
using namespace System;
using namespace System::Collections::Generic;
class _DATAWRAPPERINOUT InteractorHLWrapper
{
	gcroot<Observable^> _observable;
public:
	InteractorHLWrapper(void);
	~InteractorHLWrapper(void);
	InteractorHLWrapper(gcroot<Observable^> obs);

	void NotifyObserver();
};


