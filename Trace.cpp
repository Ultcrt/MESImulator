#include "Trace.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<Instruction> TraceLoader::Load(std::string path)
{
    ifstream traceFileStream(path, ios::in);

    vector<Instruction> instructions;

    if (!traceFileStream.is_open()) {
        return instructions;
    }

    string line;
    while (getline(traceFileStream, line)) {
        instructions.emplace_back(line);
    }

    return instructions;
}