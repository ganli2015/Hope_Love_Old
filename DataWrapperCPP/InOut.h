#pragma once
#pragma warning(disable:4251)

#include <vector>
#include <memory>
#include <string>
#include "../CommonTools/MyObject.h"
using std::tr1::shared_ptr;

#ifdef DATAWRAPPERAPI
#define _DATAWRAPPERINOUT _declspec(dllexport)
#else
#define _DATAWRAPPERINOUT _declspec(dllimport)
#endif

