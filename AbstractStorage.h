#pragma once

#include "State.h"
#include "Instruction.h"

class Bus;

class AbstractStorage
{
public:
	AbstractStorage();
	bool SetBusPtr(Bus* pBus);
	virtual bool Link(Bus* pBus) = 0;

protected:
	Bus* pBus;
};

