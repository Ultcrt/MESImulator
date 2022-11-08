#pragma once

#include "Cache.h"
#include "Instruction.h"
#include "Memory.h"
#include <vector>

class Bus
{
public:
	bool PushBackCachePtr(Cache* pCache);
	bool SetMemoryPtr(Memory* pMemory);
	bool Link(Cache* pCache);
	bool Link(Memory* pMemory);
	size_t BroadcastInvalid(Cache* src, size_t startAddress);
	Cache* RequestModifiedOrExclusiveDataFromRemote(Cache* src, size_t startAddress);
	bool WriteBackToMemory(size_t startAddress);

private:
	std::vector<Cache*> pCaches;
	Memory* pMemory;
};

