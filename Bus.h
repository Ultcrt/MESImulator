#pragma once

#include "Cache.h"
#include <string>
#include <vector>

class Bus
{
public:
	bool LinkCache(Cache cache);
	size_t Broadcast(Cache src, std::string address);

private:
	std::vector<Core> cores;
};

