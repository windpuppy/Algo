#pragma once
#include <iostream>
#include <thread>
#include <mutex> // mutex, unique_lock
#include <future> // std::this_thread
#include <condition_variable>

#include "Common.h"

std::condition_variable sender, receiver;
int count = 0; // shared between sender and receiver

class PrintOrdered {
private:
    void static send(int id) {
        std::unique_lock<std::mutex> lock(mtx);
        while (count != 0) // only send when count is reset to 0
            sender.wait(lock);
        std::cout << id << " sent, ";
        count = id;
        receiver.notify_one();
    }

    void static receive() {
        std::unique_lock<std::mutex> lock(mtx);
        while (count == 0) // receive when there is a new count/id
            receiver.wait(lock);
        std::cout << count << " received.\n";
        count = 0;
        sender.notify_one();
    }

public:
    void print_ordered() {
        std::vector<std::thread> senderThreads(10), receiverThreads(10);
        // spawn 20 threads, 10 each
        for (int i = 0; i < 10; ++i) {
            senderThreads[i] = std::thread(send, i + 1);
            receiverThreads[i] = std::thread(receive);
        }

        std::for_each(senderThreads.begin(), senderThreads.end(), std::mem_fn(&std::thread::join));
        std::for_each(receiverThreads.begin(), receiverThreads.end(), std::mem_fn(&std::thread::join));

        std::cout << std::endl;
    }
};