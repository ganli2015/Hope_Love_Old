#include <vector>
#include <map>
#include <memory>
#include <assert.h>
#include <string>
#include <math.h>
#include <algorithm>
#include <iterator>
#include <fstream>

//#include "FuncForTest.h"
#include "../CommonTools/MyObject.h"
#include "../CommonTools/assertions.h"

using namespace std;

#ifdef UTFACILITY
#define _UTFACILITYINOUT _declspec(dllexport)
#else
#define _UTFACILITYINOUT _declspec(dllimport)
#endif
