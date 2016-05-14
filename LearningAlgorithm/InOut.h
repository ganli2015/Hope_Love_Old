#pragma once
#pragma warning(disable:4251)


#include <vector>
#include <memory>
#include <assert.h>
#include <string>
#include <algorithm>
#include "../CommonTools/MyPtr.h"
using namespace std::tr1;
using namespace std;


#ifdef LEARNINGALGORITHMAPI
#define _LEARNINGALGORITHMINOUT _declspec(dllexport)
#else
#define _LEARNINGALGORITHMINOUT _declspec(dllimport)
#endif