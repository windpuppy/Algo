#pragma once

#include <iostream>
#include <thread>
#include <mutex> // mutex, unique_lock
#include <future> // std::this_thread
#include <condition_variable>

std::mutex mtx;

