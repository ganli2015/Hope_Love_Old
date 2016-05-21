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


void MyObject::operator delete( void* p )
{
#ifdef _DEBUG

	vector<MyObject*>::iterator it=find(objectsVec.begin(),objectsVec.end(),p);
	objectsVec.erase(it);

	MyObject::count--;
	out<<MyObject::count<<endl;
#endif // _DEBUG

	free(p);
}

void* MyObject::operator new( size_t size )
{
	void* p = malloc(size);  

#ifdef _DEBUG
	MyObject::count++;
	objectsVec.push_back(reinterpret_cast<MyObject*>(p));
	out<<MyObject::count<<endl;
#endif // _DEBUG

	return p;
}






