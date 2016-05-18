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

#ifdef _DEBUG

void MyObject::operator delete( void* p )
{
	vector<MyObject*>::iterator it=find(objectsVec.begin(),objectsVec.end(),p);
	objectsVec.erase(it);
	free(p);

	MyObject::count--;
	out<<MyObject::count<<endl;

}

void* MyObject::operator new( size_t size )
{
	void* p = malloc(size);  

	MyObject::count++;
	objectsVec.push_back(reinterpret_cast<MyObject*>(p));
	out<<MyObject::count<<endl;

	return p;
}

#endif // _DEBUG





