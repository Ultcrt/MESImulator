#pragma once

#include <map>
#include "State.h"

class Cache
{
public:
	Cache(size_t cacheLineLen, size_t maxCacheLine, Bus bus);
	bool LocalRead(size_t address);
	bool LocalWrite(size_t address);
	bool RemoteRead(size_t address);
	bool RemoteWrite(size_t address);

private:
	std::map<size_t, State> cacheLines;
};

