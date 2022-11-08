#include "State.h"

std::string GetStateName(State state)
{
	switch (state)
	{
	case State::Modified:
		return "Modified";
	case State::Exclusive:
		return "Exclusive";
	case State::Shared:
		return "Shared";
	case State::Invalid:
		return "Invalid";
	default:
		return "Undefined";
	}
}
