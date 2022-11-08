#pragma once

#include "Operation.h"
#include <string>

enum class State
{
	Modified,
	Exclusive,
	Shared,
	Invalid
}; 

std::string GetStateName(State state);