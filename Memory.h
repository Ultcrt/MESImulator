#pragma once

#include "AbstractStorage.h"

class Bus;

class Memory: public AbstractStorage
{
public:
	bool Update(size_t startAddress);
	virtual bool Link(Bus* pBus);
	Memory(size_t maxMemorySize);
	
private:
	size_t maxMemorySize;
};

