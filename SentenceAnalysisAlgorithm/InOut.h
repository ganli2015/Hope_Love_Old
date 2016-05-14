#pragma once
#pragma warning(disable:4251)


#include <vector>
#include <memory>
#include <assert.h>
#include <string>
#include <algorithm>
using namespace std::tr1;
using namespace std;

#include "../CommonTools/CommonDeleteFunction.h"
#include "../CommonTools/assertions.h"
#include "../CommonTools/MyPtr.h"


#ifdef SENTENCEANALYSISALGORITHMAPI
#define _SENTENCEANALYSISALGORITHMINOUT _declspec(dllexport)
#else
#define _SENTENCEANALYSISALGORITHMINOUT _declspec(dllimport)
#endif
