#pragma once
#pragma warning(disable:4251)
#include "InOut.h"

#include <map>
#include <stdlib.h>  


class _COMMONTOOLSINOUT MyObject
{
	static int count;
	static vector<MyObject*> objectsVec;
	static ofstream out;

public:
	MyObject();
	virtual ~MyObject();

	static int GetObjectCount() {return count;}	

private:


public:


	void operator delete(void* p);  

	void* operator new(size_t size);

	
};

