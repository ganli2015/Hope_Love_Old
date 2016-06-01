#pragma once
#pragma warning(disable:4251)
#include "InOut.h"

#include <map>
#include <stdlib.h>  
#include <fstream>

///MyObject contains information of total objects.
class _COMMONTOOLSINOUT MyObject
{

protected:
	static ofstream out;
	static int count;
	static vector<MyObject*> objectsVec;

public:
	MyObject();
	virtual ~MyObject();

	static int GetObjectCount() {return count;}	
};

///An Object contains type information.
template<class T>
class Obj : private MyObject
{
public:

	void operator delete(void* p);  

	void* operator new(size_t size);
};

template<class T>
void Obj<T>::operator delete( void* p )
{
#ifdef _DEBUG

	vector<MyObject*>::iterator it=find(objectsVec.begin(),objectsVec.end(),p);
	objectsVec.erase(it);

	MyObject::count--;
	out<<MyObject::count<<" "<<typeid(T).name()<<endl;
#endif // _DEBUG

	free(p);
}

template<class T>
void* Obj<T>::operator new( size_t size )
{
	void* p = malloc(size);  

#ifdef _DEBUG
	MyObject::count++;
	objectsVec.push_back(reinterpret_cast<MyObject*>(p));
	out<<MyObject::count<<" "<<typeid(T).name()<<endl;
#endif // _DEBUG

	return p;
}
