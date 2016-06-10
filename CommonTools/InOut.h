#pragma once
#pragma warning(disable:4251)

#include <vector>
#include <memory>
#include <assert.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <map>
#include <stdlib.h>
using namespace std::tr1;
using namespace std;

#ifdef  COMMONTOOLSAPI
#define _COMMONTOOLSINOUT _declspec(dllexport)
#else
#define _COMMONTOOLSINOUT _declspec(dllimport)
#endif