// Threading.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <mutex> // mutex, unique_lock
#include <condition_variable>

std::condition_variable cv;
bool ready = false;

std::mutex mtx;
std::condition_variable sender, receiver;
int count = 0; // shared between sender and receiver

void print_block(int n, char c) {
    std::unique_lock<std::mutex> lock(mtx);
    for (int i = 0; i < n; ++i)
        std::cout << c;
    std::cout << std::endl;
}

void print_two_lines()
{
    std::thread t1(print_block, 50, 'a');
    std::thread t2(print_block, 50, 'b');

    t1.join();
    t2.join();
}

void print_id(int id) {
    std::unique_lock<std::mutex> lock(mtx);
    while (!ready)
        cv.wait(lock);
    std::cout << "Thread " << id << " completed.\n";
}

void go() {
    std::unique_lock<std::mutex> lock(mtx);
    ready = true;
    cv.notify_all();
}

// Will print 10 threads in any order
void print_race() {
    std::thread threads[10];
    // spawn 10 threads
    for (int i = 0; i < 10; ++i) {
        threads[i] = std::thread(print_id, i + 1);
    }

    go();
    //std::unique_lock<std::mutex> lock(mtx);
    //ready = true;
    //cv.notify_all();
    //lock.unlock();

    for (auto& t : threads)
        t.join();
}

void send(int id) {
    std::unique_lock<std::mutex> lock(mtx);
    while (count != 0) // only send when count is reset to 0
        sender.wait(lock);
    count = id;
    receiver.notify_one();
}

void receive() {
    std::unique_lock<std::mutex> lock(mtx);
    while (count == 0) // receive when there is a new count/id
        receiver.wait(lock);
    std::cout << count << " received.\n";
    count = 0;
    sender.notify_one();
}

void print_send_receive() {
    std::thread senders[10], receivers[10];
    // spawn 20 threads, 10 each
    for (int i = 0; i < 10; ++i) {
        senders[i] = std::thread(send, i + 1);
        receivers[i] = std::thread(receive);
    }

    for (int i = 0; i < 10; ++i) {
        senders[i].join();
        receivers[i].join();
    }
}

int main()
{
    //print_two_lines();
    
    print_race();

    //print_send_receive();

    return 0;
}


