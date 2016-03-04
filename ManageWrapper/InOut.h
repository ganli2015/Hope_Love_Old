#pragma once

#include <memory>
#include <assert.h>

#ifdef MANAGEWRAPPERAPI
#define _MANAGEWRAPPERINOUT _declspec(dllexport)
#else
#define _MANAGEWRAPPERINOUT _declspec(dllimport)
#endif

