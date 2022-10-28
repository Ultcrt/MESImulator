#pragma once

#include "Operation.h"

enum class State
{
	Modified,
	Exclusive,
	Shared,
	Invalid
}; 

State GetNewStateAfterOperation(State currentState, Operation, bool fromRemote);
