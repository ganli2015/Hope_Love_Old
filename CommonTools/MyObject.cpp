#include "StdAfx.h"
#include "MyObject.h"

#include <fstream>

#include "assertions.h"

int MyObject::count=0;

vector<MyObject*> MyObject::objectsVec;

std::ofstream MyObject::out("Objects.txt");


MyObject::MyObject()
{
}

MyObject::~MyObject()
{

}








