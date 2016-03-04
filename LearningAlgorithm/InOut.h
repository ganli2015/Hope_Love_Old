#pragma once
#pragma warning(disable:4251)


#include <vector>
#include <memory>
#include <assert.h>
#include <string>
#include <algorithm>
using namespace std::tr1;
using namespace std;


#ifdef LEARNINGALGORITHMAPI
#define _LEARNINGALGORITHMINOUT _declspec(dllexport)
#else
#define _LEARNINGALGORITHMINOUT _declspec(dllimport)
#endif