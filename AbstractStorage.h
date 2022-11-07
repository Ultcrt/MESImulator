#pragma once

#include <map>
#include "State.h"
#include "Bus.h"
#include "Instruction.h"

class AbstractStorage
{
public:
	AbstractStorage(size_t unitLen, size_t maxUnits, Bus* pBus);
	bool SetBusPtr(Bus* pBus);
	size_t GetStartAddress(size_t address);

	virtual bool Link(Bus* pBus) = 0;

protected:
	size_t unitLen;
	size_t maxUnits;
	Bus* pBus;
};

