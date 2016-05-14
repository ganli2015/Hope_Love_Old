#pragma once

#include <memory>
#include <assert.h>
#include "../CommonTools/MyPtr.h"

#ifdef MANAGEWRAPPERAPI
#define _MANAGEWRAPPERINOUT _declspec(dllexport)
#else
#define _MANAGEWRAPPERINOUT _declspec(dllimport)
#endif

