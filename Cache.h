#pragma once

#include <map>
#include "State.h"
#include "Bus.h"
#include "AbstractStorage.h"

class Cache: public AbstractStorage
{
public:
	Cache(size_t cacheLineLen, size_t maxCacheLine, Bus* pBus);
	virtual bool ReceiveLocalInstruction(Instruction instruction);
	virtual bool ReceiveRemoteInstruction(Instruction instruction);
	virtual bool Link(Bus* pBus);

private:
	std::map<size_t, State> units;
	State GetCacheLineState(size_t address);
	State LoadFromMemory(size_t startAddress);
};

