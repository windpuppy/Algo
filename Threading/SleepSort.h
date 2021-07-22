#pragma once

#include "Common.h"

class SleepSort {
private:
    void static wait(int n) {
        std::this_thread::sleep_for(std::chrono::milliseconds(n * 500));
        std::cout << n << "...";
    }

public:
    void sleepSort(std::vector<int>& nums) {
        std::vector<std::thread> threadList;
        for (auto n : nums)
            threadList.push_back(std::thread(wait, n));

        std::for_each(threadList.begin(), threadList.end(), std::mem_fn(&std::thread::join));

        std::cout << std::endl;
    }
};
