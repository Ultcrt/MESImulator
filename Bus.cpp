#include "Bus.h"

using namespace std;

bool Bus::PushBackCachePtr(Cache* pStorage)
{
    pCaches.push_back(pStorage);
    return true;
}

bool Bus::SetMemoryPtr(Memory* pMemory)
{
    this->pMemory = pMemory;
    return true;
}

bool Bus::Link(Cache* pCache)
{
    pCaches.push_back(pCache);
    pCache->SetBusPtr(this);
    return true;
}

bool Bus::Link(Memory* pMemory)
{
    this->pMemory = pMemory;
    pMemory->SetBusPtr(this);
    return true;
}

size_t Bus::Broadcast(Cache* src, Instruction instruction)
{
    size_t successCount = 0;

    for (vector<Cache*>::iterator iter = pCaches.begin(); iter < pCaches.end(); iter++) {
        if (*iter != src) {
            if ((*iter)->ReceiveRemoteInstruction(instruction)) {
                successCount++;
            }
        }
    }

    return successCount;
}

bool Bus::WriteBackToMemory(size_t startAddress)
{
    return pMemory->Update(startAddress);
}
