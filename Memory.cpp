#include "Memory.h"
#include <iostream>
#include "Bus.h"

using namespace std;

bool Memory::Update(size_t startAddress)
{
    if (startAddress < maxMemorySize) {
        // Ignore memory update detail
        cout << "\t" << "Memory: Data starting at address '" << hex << startAddress << "' has been update" << endl;
        return true;
    }
    else {
        // Ignore memory update detail
        cout << "\t" << "Memory: Address '" << hex << startAddress << "' is overflowed!" << endl;
        return false;
    }
}

bool Memory::Link(Bus* pBus)
{
    this->pBus = pBus;
    pBus->SetMemoryPtr(this);
    return true;
}

Memory::Memory(size_t maxMemorySize, string name) : AbstractStorage(name), maxMemorySize(maxMemorySize) {}
