#pragma once

#include "Common.h"

bool ready = false;
std::condition_variable cv;

class PrintRace {
private:
    void static print_id(int id) {
        std::unique_lock<std::mutex> lock(mtx);
        while (!ready)
            cv.wait(lock);
        std::cout << "Thread " << id << " completed.\n";
    }

    void go() {
        ready = true;
        cv.notify_all();
    }

public:
    // Will print 10 threads in any order
    void print_race() {
        std::thread threads[10];
        // spawn 10 threads
        for (int i = 0; i < 10; ++i) {
            threads[i] = std::thread(print_id, i + 1);
        }

        go();

        for (auto& t : threads)
            t.join();

        std::cout << std::endl;
    }
};