#include "StdAfx.h"
#include "InteractorHLWrapper.h"


InteractorHLWrapper::InteractorHLWrapper(void)
{
}

InteractorHLWrapper::InteractorHLWrapper( gcroot<Observable^> obs )
{
	_observable=obs;
}


InteractorHLWrapper::~InteractorHLWrapper(void)
{
}

void InteractorHLWrapper::NotifyObserver()
{
	_observable->NotifyObserver();
}
