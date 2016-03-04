#pragma once
#pragma warning(disable:4251)


#include <vector>
#include <map>
#include <memory>
#include <assert.h>
#include <string>
#include <algorithm>
using namespace std::tr1;
using namespace std;

#ifdef REACTIONANALYSISALGORITHMAPI
#define _REACTIONANALYSISALGORITHMINOUT _declspec(dllexport)
#else
#define _REACTIONANALYSISALGORITHMINOUT _declspec(dllimport)
#endif 

