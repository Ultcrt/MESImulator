#pragma once

#include "Instruction.h"
#include "Bus.h"
#include "Cache.h"

class Core
{
public:
	Core(Cache* pCache);
	bool Execute(Instruction instruction);

private:
	Cache* pCache;
};

