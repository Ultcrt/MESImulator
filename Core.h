#pragma once

#include "Instruction.h"
#include "Bus.h"

class Core
{
public:
	Core(Cache* cache);
	bool Execute(Instruction instruction);

private:
	Cache* pCache;
};

