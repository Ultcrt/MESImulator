#include "Core.h"

Core::Core(Cache* pCache) : pCache(pCache) {}

bool Core::Execute(Instruction instruction) {
	return pCache->ReceiveLocalInstruction(instruction);
}
