#pragma once

#include <memory>
#include <vector>
#include <algorithm>

#define MATHMATICAPI
#ifdef MATHMATICAPI
#define _MATHMATICINOUT _declspec(dllexport)
#else
#define _MATHMATICINOUT _declspec(dllimport)
#endif

