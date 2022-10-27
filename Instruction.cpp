#include "Instruction.h"

#include <string>
#include <sstream>

using namespace std;

Instruction::Instruction(string fileLine)
{
    istringstream fileLineStream(fileLine);

    size_t operationCode;

    fileLineStream >> operationCode >> hex >> this->address;

    this->operation = Operation(operationCode);
}