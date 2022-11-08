#pragma once

#include "AbstractStorage.h"
#include <map>
#include "State.h"
#include <string>

class Bus;

class Cache: public AbstractStorage
{
public:
	Cache(size_t cacheLineLen, size_t maxCacheLine, std::string name);
	bool ReceiveLocalInstruction(Instruction instruction);
	bool SetInvalid(size_t startAddress);
	bool SendModifiedOrExclusiveData(size_t startAddress);
	virtual bool Link(Bus* pBus);

private:
	std::map<size_t, State> cacheLines;
	State GetCacheLineState(size_t startAddress);
	bool LoadFromMemory(size_t startAddress);
	size_t cacheLineLen;
	size_t maxCacheLines;
	size_t GetStartAddress(size_t address);
	void PrintCacheState(size_t startAddress, State lastState);
	bool SwapOutWhenNeeded(size_t startAddress);
};

