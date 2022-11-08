#include "AbstractStorage.h"

using namespace std;

AbstractStorage::AbstractStorage(string name): pBus(nullptr), name(name) {}

bool AbstractStorage::SetBusPtr(Bus* pBus)
{
	this->pBus = pBus;
	return true;
}