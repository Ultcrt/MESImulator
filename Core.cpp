#include "Core.h"
#include <iostream>
#include "Operation.h"

using namespace std;

Core::Core(Cache* pCache) : pCache(pCache) {}

bool Core::Execute(Instruction instruction) {
	cout << "Core: " << GetOperationName(instruction.operation) << " address at '" << hex << instruction.address << "'" << endl;
	return pCache->ReceiveLocalInstruction(instruction);
}
