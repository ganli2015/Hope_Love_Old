#include "StdAfx.h"
#include "MyObject.h"

#include <fstream>

#include "assertions.h"

int MyObject::count=0;

vector<MyObject::MyObjectInfo> MyObject::objectsVec;

std::ofstream MyObject::out("Objects.txt");


MyObject::MyObject()
{
}

MyObject::~MyObject()
{

}

std::string MyObject::CurrentObjInfo()
{
	string res="";

	for (unsigned int i=0;i<objectsVec.size();++i)
	{
		res+=objectsVec[i].classname+"\n";
	}

	return res;
}








