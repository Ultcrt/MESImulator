#include "AbstractStorage.h"

AbstractStorage::AbstractStorage(size_t unitLen, size_t maxUnits, Bus* pBus): unitLen(unitLen), maxUnits(maxUnits), pBus(pBus) {}

bool AbstractStorage::SetBusPtr(Bus* pBus)
{
	this->pBus = pBus;
	return true;
}

size_t AbstractStorage::GetStartAddress(size_t address)
{
	return (address / unitLen) * unitLen;
}
