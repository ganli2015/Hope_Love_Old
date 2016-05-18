#pragma once
#pragma warning(disable:4251)
#pragma warning(disable:4275)

#include <vector>
#include <map>
#include <memory>
#include <assert.h>
#include <string>
#include <math.h>
#include <algorithm>
#include <iterator>
#include "../CommonTools/MyObject.h"

using namespace std;
using std::tr1::shared_ptr;

#ifdef  NEURALNETWORKDESIGNAPI
#define _NEURALNETWORKDESIGNINOUT _declspec(dllexport)
#else
#define _NEURALNETWORKDESIGNINOUT _declspec(dllimport)
#endif
