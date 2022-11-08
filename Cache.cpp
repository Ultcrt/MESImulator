#include "Cache.h"
#include "Bus.h"
#include <iostream>

using namespace std;

Cache::Cache(size_t cacheLineLen, size_t maxCacheLines, string name): AbstractStorage(name), cacheLineLen(cacheLineLen), maxCacheLines(maxCacheLines)
{
	if (maxCacheLines > this->cacheLines.max_size() || maxCacheLines < 1) {
		this->maxCacheLines = this->cacheLines.max_size();
	}
	else {
		this->maxCacheLines = maxCacheLines;
	}
}

bool Cache::ReceiveLocalInstruction(Instruction instruction)
{
	size_t startAddress = GetStartAddress(instruction.address);

	State lastState = GetCacheLineState(startAddress);

	switch (lastState)
	{
	case State::Modified:
		switch (instruction.operation)
		{
		case Operation::Read:
			// Remain the same
			break;
		case Operation::Write:
			// Remain the same
			break;
		}
		break;
	case State::Exclusive:
		switch (instruction.operation)
		{
		case Operation::Read:
			// Remain the same
			break;
		case Operation::Write:
			// Change to Modified
			cacheLines[startAddress] = State::Modified;
			// Make others invalid
			pBus->BroadcastInvalid(this, startAddress);
			break;
		}
		break;
	case State::Shared:
		switch (instruction.operation)
		{
		case Operation::Read:
			// Remain the same
			break;
		case Operation::Write:
			// Write back to memory
			pBus->WriteBackToMemory(startAddress);
			// Change to Exclusive
			cacheLines[startAddress] = State::Exclusive;
			// Make others invalid
			pBus->BroadcastInvalid(this, startAddress);
			break;
		}
		break;
	case State::Invalid:
		// Invalid has two possible situations: 1. startAddress not in cache; 2. set invalid by remote;
		switch (instruction.operation)
		{
		case Operation::Read:
			// Swap out other cache line when needed (currently when cache is full and startAddress is not in cache)
			SwapOutWhenNeeded(startAddress);
			// Ask for others
			if (!pBus->RequestModifiedOrExclusiveDataFromRemote(this, startAddress)) {
				// Others don't have, then load from memory
				LoadFromMemory(startAddress);
			}
			// Change to Shared
			cacheLines[startAddress] = State::Shared;
			break;
		case Operation::Write:
			// Swap out other cache line when needed (currently when cache is full and startAddress is not in cache)
			SwapOutWhenNeeded(startAddress);
			// Ask for others
			if (!pBus->RequestModifiedOrExclusiveDataFromRemote(this, startAddress)) {
				// Others don't have, then load from memory
				LoadFromMemory(startAddress);
			}
			// Write back to memory
			pBus->WriteBackToMemory(startAddress);
			// Change to Exclusive
			cacheLines[startAddress] = State::Exclusive;
			// Make others invalid
			pBus->BroadcastInvalid(this, startAddress);
			break;
		}
		break;
	}

	PrintCacheState(startAddress, lastState);

	return true;
}

bool Cache::SetInvalid(size_t startAddress)
{
	if (cacheLines.find(startAddress) != cacheLines.end()) {
		State lastState = GetCacheLineState(startAddress);
		cacheLines[startAddress] = State::Invalid;

		PrintCacheState(startAddress, lastState);
		
		return true;
	}
	return false;
}

bool Cache::SendModifiedOrExclusiveData(size_t startAddress)
{
	if (cacheLines.find(startAddress) != cacheLines.end()) {
		if (cacheLines[startAddress] == State::Exclusive or cacheLines[startAddress] == State::Modified) {
			State lastState = GetCacheLineState(startAddress);
			// Change to Shared
			cacheLines[startAddress] = State::Shared;

			PrintCacheState(startAddress, lastState);

			return true;
		}
	}
	return false;
}

State Cache::GetCacheLineState(size_t startAddress)
{
	std::map<size_t, State>::iterator position = cacheLines.find(startAddress);

	if (position != cacheLines.end()) {
		// Hit
		return position->second;
	}
	else {
		// Miss
		return State::Invalid;
	}
}

bool Cache::SwapOutWhenNeeded(size_t startAddress) {
	if (cacheLines.find(startAddress) != cacheLines.end()) {
		// startAddress does not exist in cache, need to check cache is full or not
		if (cacheLines.size() >= maxCacheLines) {
			// Swap out the first Cache line
			size_t firstCacheLineAddress = cacheLines.begin()->first;
			State firstCacheLineState = cacheLines.begin()->second;

			if (firstCacheLineState == State::Modified) {
				// Need to write back to memory only if swapped out cache line at modified mode
				pBus->WriteBackToMemory(firstCacheLineAddress);
			}

			cacheLines.erase(cacheLines.begin());

			return true;
		}
	}
	return false;
}

bool Cache::LoadFromMemory(size_t startAddress)
{
	cacheLines[startAddress] = State::Shared;
	cout << "\t" << "Cache[" << name << "]: Cache line starting at address '" << hex << startAddress << "' has been loaded from memory" << endl;
	return true;
}

bool Cache::Link(Bus* pBus)
{
	this->pBus = pBus;
	pBus->PushBackCachePtr(this);
	return false;
}

size_t Cache::GetStartAddress(size_t address)
{
	return (address / cacheLineLen) * cacheLineLen;
}

void Cache::PrintCacheState(size_t startAddress, State lastState)
{
	if (cacheLines[startAddress] == lastState) {
		cout << "\t" << "Cache[" << name << "]: Cache line starting at address '" << hex << startAddress << "' has remained at the same state '" << GetStateName(cacheLines[startAddress]) << "'" << endl;
	}
	else {
		cout << "\t" << "Cache[" << name << "]: Cache line starting at address '" << hex << startAddress << "' has changed from '" << GetStateName(lastState) << "' to '" << GetStateName(cacheLines[startAddress]) << "'" << endl;
	}
}

