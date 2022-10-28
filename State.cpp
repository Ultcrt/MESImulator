#include "State.h"

State GetNewStateAfterOperation(State currentState, Operation operation, bool fromRemote)
{
	switch (currentState)
	{
	case State::Modified:
		switch (operation)
		{
		case Operation::Read:
			if (fromRemote) {
				return State::Shared;
			}
			else {

			}
			break;
		case Operation::Write:
			break;
		default:
			break;
		}
		break;
	case State::Exclusive:
		break;
	case State::Shared:
		break;
	case State::Invalid:
		break;
	default:
		break;
	}
}
