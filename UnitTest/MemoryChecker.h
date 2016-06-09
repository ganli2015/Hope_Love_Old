#pragma once
#include <string>
#include <fstream>

#define MEMOCHECK MemoryChecker mc(__FUNCTION__)
#define RELEASE_MEMOCHECK mc.~MemoryChecker()

class MemoryChecker
{
	int _startObjCount;
	std::string _functionName;

	static std::ofstream out;
public:
	MemoryChecker(void);
	MemoryChecker(const std::string function);
	~MemoryChecker(void);
};

