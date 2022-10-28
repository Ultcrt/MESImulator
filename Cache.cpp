#include "Cache.h"

Cache::Cache(size_t cacheLineLen, size_t maxCacheLine, Bus* pBus): AbstractStorage(cacheLineLen, maxCacheLine, pBus) 
{
	if (maxUnits > this->units.max_size() || maxUnits < 1) {
		this->maxUnits = this->units.max_size();
	}
	else {
		this->maxUnits = maxUnits;
	}
}

bool Cache::ReceiveLocalInstruction(Instruction instruction)
{
	State currentState = GetCacheLineState(instruction.address);

	//TODO

	pBus->Broadcast(this, instruction);
	return true;
}

bool Cache::ReceiveRemoteInstruction(Instruction instruction)
{
	State currentState = GetCacheLineState(instruction.address);

	//TODO

	return false;
}

State Cache::GetCacheLineState(size_t address)
{
	size_t startAddress = GetStartAddress(address);

	std::map<size_t, State>::iterator position = units.find(startAddress);

	if (position != units.end()) {
		// Hit
		return position->second;
	}
	else {
		// Miss
		return LoadFromMemory(startAddress);
	}
	return State();
}

State Cache::LoadFromMemory(size_t startAddress)
{
	if (units.size() >= maxUnits) {
		// Swap out the first Cache line
		size_t firstCacheLineAddress = units.begin()->first;
		State firstCacheLineState = units.begin()->second;

		if (firstCacheLineState == State::Modified) {
			// Need to write back to memory only if swapped out cache line at modified mode
			pBus->WriteBackToMemory(firstCacheLineAddress);
		}

		units.erase(units.begin());
	}

	units[startAddress] = State::Shared;
	return State::Shared;
}

bool Cache::Link(Bus* pBus)
{
	this->pBus = pBus;
	pBus->PushBackCachePtr(this);
	return false;
}
