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
#include <fstream>
#include "../CommonTools/assertions.h"


using std::tr1::shared_ptr;
using namespace std;

#ifdef  MINDELEMENTAPI
#define _MINDELEMENTINOUT _declspec(dllexport)
#else
#define _MINDELEMENTINOUT _declspec(dllimport)
#endif