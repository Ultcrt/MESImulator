#include "Cache.h"
#include "Bus.h"

Cache::Cache(size_t cacheLineLen, size_t maxCacheLines): cacheLineLen(cacheLineLen), maxCacheLines(maxCacheLines)
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

	State currentState = GetCacheLineState(startAddress);

	switch (currentState)
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
			// Make others invalid
			pBus->BroadcastInvalid(this, startAddress);
			// Change to Modified
			cacheLines[startAddress] = State::Modified;
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
			// Make others invalid
			pBus->BroadcastInvalid(this, startAddress);
			// Write back to memory
			pBus->WriteBackToMemory(startAddress);
			// Change to Exclusive
			cacheLines[startAddress] = State::Exclusive;
			break;
		}
		break;
	case State::Invalid:
		switch (instruction.operation)
		{
		case Operation::Read:
			// Ask for others
			if (!pBus->AskForModifiedOrExclusiveData(this, startAddress)) {
				// Others don't have, then load from memory
				LoadFromMemory(startAddress);
			}
			// Change to Shared
			cacheLines[startAddress] = State::Shared;
			break;
		case Operation::Write:
			// Ask for others
			if (!pBus->AskForModifiedOrExclusiveData(this, startAddress)) {
				// Others don't have, then load from memory
				LoadFromMemory(startAddress);
			}
			// Write back to memory
			pBus->WriteBackToMemory(startAddress);
			// Change to Exclusive
			cacheLines[startAddress] = State::Exclusive;
			break;
		}
		break;
	}

	return true;
}

bool Cache::SetInvalid(size_t startAddress)
{
	if (cacheLines.find(startAddress) != cacheLines.end()) {
		cacheLines[startAddress] = State::Invalid;

		return true;
	}
	return false;
}

bool Cache::SendModifiedOrExclusiveData(size_t startAddress)
{
	if (cacheLines.find(startAddress) != cacheLines.end()) {
		if (cacheLines[startAddress] == State::Exclusive or cacheLines[startAddress] == State::Modified) {
			cacheLines[startAddress] = State::Shared;

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

bool Cache::LoadFromMemory(size_t startAddress)
{
	if (cacheLines.size() >= maxCacheLines) {
		// Swap out the first Cache line
		size_t firstCacheLineAddress = cacheLines.begin()->first;
		State firstCacheLineState = cacheLines.begin()->second;

		if (firstCacheLineState == State::Modified) {
			// Need to write back to memory only if swapped out cache line at modified mode
			pBus->WriteBackToMemory(firstCacheLineAddress);
		}

		cacheLines.erase(cacheLines.begin());
	}

	cacheLines[startAddress] = State::Shared;
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

