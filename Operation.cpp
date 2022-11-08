#include "Operation.h"

std::string GetOperationName(Operation operation)
{
	switch (operation)
	{
	case Operation::Read:
		return "Read";
	case Operation::Write:
		return "Write";
	default:
		return "Undefined";
	}
}
