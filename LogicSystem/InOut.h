#pragma once
#pragma warning(disable:4251)


#include <vector>
#include <memory>
#include <assert.h>
#include <string>
#include <algorithm>
#include "../CommonTools/assertions.h"
#include "../CommonTools/MyObject.h"
using namespace std::tr1;
using namespace std;

#ifdef LOGICSYSTEMAPI
#define _LOGICSYSTEMINOUT _declspec(dllexport)
#else
#define _LOGICSYSTEMINOUT _declspec(dllimport)
#endif