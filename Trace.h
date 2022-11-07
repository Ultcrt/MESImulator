#pragma once

#include "Instruction.h"
#include <string>
#include <vector>

class TraceLoader
{
public:
	static std::vector<Instruction> Load(std::string path);
};