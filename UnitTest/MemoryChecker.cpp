#include "StdAfx.h"
#include "MemoryChecker.h"
#include "../CommonTools/MyObject.h"
#include "../CommonTools/assertions.h"

#include <gTest/gtest.h>

std::ofstream MemoryChecker::out("MemoryChecker.txt");

MemoryChecker::MemoryChecker(void):_startObjCount(MyObject::GetObjectCount())
{
}

MemoryChecker::MemoryChecker( const std::string function ):_functionName(function),_startObjCount(MyObject::GetObjectCount())
{

}


MemoryChecker::~MemoryChecker(void)
{
	int curObjCount=MyObject::GetObjectCount();
	if(_startObjCount!=curObjCount)
	{
		out<<_functionName<<endl;
		out<<MyObject::CurrentObjInfo()<<endl;
		cout<<"Memory leak!!"<<endl;
	}
	
}
