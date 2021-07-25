#pragma once

#include "Common.h"

class MainVersusWorkder {
private:
	void static print_count(int n) {
		std::unique_lock<std::mutex> lock(mtx);
		std::cout << " " << n;
	}

	void static func(int min, int max) {
		//std::unique_lock<std::mutex> lock(mtx); // can NOT lock twice
		for (int i = min; i <= max; ++i) {
			print_count(i);
		}
		std::cout << std::endl;
	}

public:
	void print_range() {
		std::thread t1(func, 0, 9);
		std::thread t2(func, 10, 19);
		std::thread t3(func, 20, 29);

		for (int i = 0; i < 10; ++i)
			print_count(-i);
		std::cout << std::endl;
		
		t1.join();
		t2.join();
		t3.join();

		// Note: t1, t2, t3 and main thread will have random order of execution
	}
};
