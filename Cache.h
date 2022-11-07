#pragma once

#include <map>
#include "State.h"
#include "Bus.h"
#include "AbstractStorage.h"

class Cache: public AbstractStorage
{
public:
	Cache(size_t cacheLineLen, size_t maxCacheLine, Bus* pBus);
	bool ReceiveLocalInstruction(Instruction instruction);
	bool SetInvalid(size_t startAddress);
	bool SendModifiedOrExclusiveData(size_t startAddress);
	virtual bool Link(Bus* pBus);

private:
	std::map<size_t, State> cacheLines;
	State GetCacheLineState(size_t startAddress);
	bool LoadFromMemory(size_t startAddress);
};

