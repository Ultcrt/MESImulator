#pragma once

#include "Operation.h"
#include <string>

struct Instruction
{
	Instruction(std::string fileLine);

	Operation operation;
	size_t address;
};

