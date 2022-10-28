#pragma once
#include "AbstractStorage.h"

class Memory: public AbstractStorage
{
public:
	bool Update(size_t startAddress);

	virtual bool Link(Bus* pBus);
	virtual bool ReceiveLocalInstruction(Instruction instruction);
	virtual bool ReceiveRemoteInstruction(Instruction instruction);
};

