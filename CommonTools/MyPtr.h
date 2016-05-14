#pragma once
#pragma warning(disable:4251)
#include "InOut.h"

#include <map>
#include <stdlib.h>  


class _COMMONTOOLSINOUT MyObject
{
	static int count;
	static int maxID;
	static map<int,MyObject*> objects;
	static vector<void*> objectsVec;

	int _id;

public:
	MyObject();
	virtual ~MyObject();

	MyObject(const MyObject& obj);

	static int GetObjectCount() {return count;}

	static void OutputObjects();

	void operator =(const MyObject& obj);
	

private:

	void InceaseObj();


public:
// 	void* operator new(size_t size, const char* file, int line)
// 	{
// 		void* p = malloc(size);  
// 
// 		_filenames.push_back(file);
// 
// 		return p;  
// 	}
// 
// 	void operator delete(void* p, const char* file, int line)  
// 	{  
// 		free(p);  
// 	}  
// 
	void operator delete(void* p)  
	{  
		vector<void*>::iterator it=find(objectsVec.begin(),objectsVec.end(),p);
		objectsVec.erase(it);
		free(p);

		MyObject::count--;
	}  
  
	void* operator new(size_t size)
	{
		void* p = malloc(size);  

		MyObject::count++;
		objectsVec.push_back(p);

		return p;  
	}
};

