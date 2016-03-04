#pragma once
#pragma warning(disable:4251)


#include <vector>
#include <memory>
#include <assert.h>
#include <string>
#include <algorithm>
using namespace std::tr1;
using namespace std;

#ifdef REACTIONLISTAPI
#define _REACTIONLISTINOUT _declspec(dllexport)
#else 
#define _REACTIONLISTINOUT _declspec(dllimport)
#endif

