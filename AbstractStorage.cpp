#include "AbstractStorage.h"

AbstractStorage::AbstractStorage() {}

bool AbstractStorage::SetBusPtr(Bus* pBus)
{
	this->pBus = pBus;
	return true;
}