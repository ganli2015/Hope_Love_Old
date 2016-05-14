#include "StdAfx.h"
#include "MyPtr.h"

#include <fstream>

#include "assertions.h"

int MyObject::count=0;

std::map<int,MyObject*> MyObject::objects;
vector<void*> MyObject::objectsVec;

int MyObject::maxID=0;

MyObject::MyObject()/*:_id(maxID)*/
{
//	InceaseObj();
}

MyObject::MyObject( const MyObject& obj )/*:_id(maxID)*/
{
//	InceaseObj();
}

MyObject::~MyObject()
{
// 	int idCount=objects.count(_id);
// 	MyObject *tmpObj=objects[_id];
// 	assert(idCount==1);
// 	Check(idCount==1);
// 
// 	objects.erase(_id);
// 
// 	--count;
}

void MyObject::InceaseObj()
{
// 	int idCount=objects.count(_id);
// 	MyObject *tmpObj=objects[_id];
// 	assert(idCount==0);
// 	Check(idCount==0);
// 
// 	objects[_id]=this;
// 	++count;
// 	++maxID;
}

void MyObject::operator=( const MyObject& obj )
{
	//_id=maxID;
	//InceaseObj();
}

void MyObject::OutputObjects()
{
	ofstream out("Objects.txt");

// 	for (map<int,MyObject*>::iterator it=objects.begin();it!=objects.end();++it)
// 	{
// 		out<<it->first<<" "<<typeid(it->second).name()<<endl;
// 	}

	for (unsigned int i=0;i<objectsVec.size();++i)
	{
		MyObject* obj=reinterpret_cast<MyObject*>(objectsVec[i]);
		out<<typeid(obj).name()<<endl;
	}

	out.close();
}




