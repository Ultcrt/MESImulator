#pragma once

#include "State.h"
#include "Instruction.h"
#include <string>

class Bus;

class AbstractStorage
{
public:
	AbstractStorage(std::string name);
	bool SetBusPtr(Bus* pBus);
	virtual bool Link(Bus* pBus) = 0;

protected:
	Bus* pBus;
	std::string name;
};

