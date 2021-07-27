// Threading.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <chrono>
#include <future> // std::this_thread

#include "PrintBlock.h"
#include "PrintRace.h"
#include "PrintOrdered.h"
#include "MainVersusWorker.h"
#include "SleepSort.h"
#include "SharedPointer.h"

int main()
{
    // Print continuous block, to demonstrate locking
    PrintBlock pb;
    pb.print_two_lines();

    // Print races, to demonstrate race condition
    PrintRace pr;
    pr.print_race();

    // Print ordered race, to demonstrate cv controlled race
    PrintOrdered po;
    po.print_ordered();

    // Main thread vs worker threads
    MainVersusWorkder mvw;
    mvw.print_range();

    // Sleep sort, just for fun
    std::vector<int> v{ 7, 10, 1, 8, 3, 5, 9, 2, 4, 6 };
    SleepSort ss;
    ss.sleepSort(v);

    // Shared pointer demo
    SharedPointer sp;
    sp.demo_reference_count();
    sp.demo_inheritence();

    return 0;
}


