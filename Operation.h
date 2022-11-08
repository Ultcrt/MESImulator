#pragma once

#include <string>

enum class Operation
{
	Read,
	Write
};

std::string GetOperationName(Operation operation);
