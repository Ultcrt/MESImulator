#pragma once

#include "Operation.h"

struct Instruction
{
	Instruction(std::string fileLine);

	Operation operation;
	size_t address;
};

