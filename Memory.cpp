#include "Memory.h"
#include <iostream>

using namespace std;

bool Memory::Update(size_t startAddress)
{
    // Ignore memory update detail
    cout << "Memory: Address '" << hex << startAddress << "' has been update" << endl;
    return true;
}

bool Memory::Link(Bus* pBus)
{
    this->pBus = pBus;
    pBus->SetMemoryPtr(this);
    return true;
}
