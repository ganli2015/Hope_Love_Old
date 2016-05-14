#pragma  once
#pragma warning(disable:4251)

#include <vector>
#include <memory>
#include <assert.h>
#include <string>
#include <algorithm>

#include "../CommonTools/MyPtr.h"

#ifdef COMMANDAPI
#define _COMMANDINOUT _declspec(dllexport)
#else
#define _COMMANDINOUT _declspec(dllimport)
#endif