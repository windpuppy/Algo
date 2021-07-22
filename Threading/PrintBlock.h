#pragma once

#include "Common.h"

class PrintBlock {
private:
    void static print_block(int n, char c) {
        std::unique_lock<std::mutex> lock(mtx);
        for (int i = 0; i < n; ++i)
            std::cout << c;
        std::cout << std::endl;
    }

public:
    void print_two_lines()
    {
        std::thread t1(print_block, 50, 'a');
        std::thread t2(print_block, 50, 'b');

        t1.join();
        t2.join();

        std::cout << std::endl;
    }
};