#pragma once
#include "InOut.h"

namespace CommonTool
{
// 	template<class T>
// 	shared_ptr<T> val2sptr(const T t)
// 	{
// 		return shared_ptr<T>(new T(t));
// 	}

	template<class T>
	shared_ptr<T> ptr2sptr(T* t)
	{
		return shared_ptr<T>(t);
	}

	template<class T>
	T* sptr2ptr(shared_ptr<T> t)
	{
		return &(*t);
	}
}

