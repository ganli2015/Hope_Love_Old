#pragma once
#include "PublicHeader.h"

class Test
{
public:
	Test(void){};
	virtual ~Test(void){};

	virtual void Run()=0;
};

template<class T>
class MyTest : public Test
{
public:
	MyTest(void){};
	virtual ~MyTest(void){};

	virtual void Run()
	{
		T::RunTest();
	}
};

