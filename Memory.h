#pragma once

#include "AbstractStorage.h"
#include <string>

class Bus;

class Memory: public AbstractStorage
{
public:
	bool Update(size_t startAddress);
	virtual bool Link(Bus* pBus);
	Memory(size_t maxMemorySize, std::string name="memory");
	
private:
	size_t maxMemorySize;
};

