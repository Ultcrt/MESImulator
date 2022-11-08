// MESImulator.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include "Core.h"
#include "Bus.h"
#include "Cache.h"
#include "Trace.h"
#include "Memory.h"
#include "Instruction.h"

using namespace std;

#define CACHE_LINE_LEN 32
#define MAX_CACHE_LINES 0

int main()
{
    Bus bus;

    Cache cacheA = Cache(CACHE_LINE_LEN, MAX_CACHE_LINES);
    Cache cacheB = Cache(CACHE_LINE_LEN, MAX_CACHE_LINES);

    Core coreA = Core(&cacheA);
    Core coreB = Core(&cacheB);

    Memory memory = Memory(SIZE_MAX);

    bus.Link(&cacheA);
    bus.Link(&cacheB);
    bus.Link(&memory);

    vector<Instruction> instructionsA = TraceLoader::Load("./trace0.txt");
    vector<Instruction> instructionsB = TraceLoader::Load("./trace1.txt");

    size_t loop = max(instructionsA.size(), instructionsB.size());

    for (int i = 0; i < loop; i++) {
        if (i < instructionsA.size()) {
            coreA.Execute(instructionsA[i]);
        }
        if (i < instructionsB.size()) {
            coreB.Execute(instructionsB[i]);
        }
    }

    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
