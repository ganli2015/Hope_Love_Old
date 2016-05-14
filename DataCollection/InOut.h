#pragma once
#pragma warning(disable:4251)

#include <vector>
#include <memory>
#include <assert.h>
#include <string>
#include <algorithm>
#include <iterator>
#include <assert.h>
using namespace std::tr1;
using namespace std;

#include "../CommonTools/CommonDeleteFunction.h"
#include "../CommonTools/CommonTranslateFunction.h"
#include "../CommonTools/MyPtr.h"

#ifdef  DATACOLLECTIONAPI
#define _DATACOLLECTIONINOUT _declspec(dllexport)
#else
#define _DATACOLLECTIONINOUT _declspec(dllimport)
#endif

