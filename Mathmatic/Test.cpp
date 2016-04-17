#include "Stdafx.h"
#include "InOut.h"
#include "Rand.h"
#include "TestClass.h"

#include <windows.h>


int __cdecl main()
{
	TestClass::RunTest();
	//TestClass::TestRand();
	//TestClass::TestMyInt();
	system("Pause");

	return 0;
}