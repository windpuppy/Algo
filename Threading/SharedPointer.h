#pragma once
#include "Common.h"

using namespace std;

class SharedPointer {
private:
	void print_counter(int n) {
		cout << "Ref count: " << n << endl;
	}

	void foo(shared_ptr<int> p) {
		print_counter(p.use_count());
	}

	struct Base
	{
		Base() { std::cout << "  Base::Base()" << endl; }
		// Note: non-virtual destructor is OK here
		~Base() { std::cout << "  Base::~Base()" << endl; }
	};

	struct Derived : public Base
	{
		Derived() { std::cout << "  Derived::Derived()" << endl; }
		~Derived() { std::cout << "  Derived::~Derived()" << endl; }
	};

	void static bar(shared_ptr<Base> p)
	{
		this_thread::sleep_for(chrono::seconds(1));
		shared_ptr<Base> lp = p; // thread-safe, even though the shared use_count is incremented
		{
			static mutex io_mutex;
			lock_guard<mutex> lk(io_mutex);
			cout << "local ptr in a thread: " << endl;
			cout << "  lp.get() = " << lp.get() << ", lp.use_count() = " << lp.use_count() << endl;
		}
	}
public:
	void demo_reference_count() {
		auto p1 = std::make_shared<int>(0);
		print_counter(p1.use_count()); // 1

		{
			auto p2 = p1;
			print_counter(p2.use_count()); // 2
			print_counter(p1.use_count()); // 2

			foo(p2); // inside it, will print 3
			print_counter(p2.use_count()); // 2
		}

		print_counter(p1.use_count()); // 1

		auto p3 = p1;
		print_counter(p3.use_count()); // 2
		print_counter(p1.use_count()); // 2

		p1.reset();
		print_counter(p1.use_count()); // 0
		print_counter(p3.use_count()); // 1, NOT ZERO!

		cout << endl;
	}

	void demo_inheritence() {
		shared_ptr<Base> p = make_shared<Derived>();

		cout << "Created a shared Derived (as a pointer to Base)" << endl;
		cout << "  p.get() = " << p.get() << ", p.use_count() = " << p.use_count() << endl;
		thread t1(bar, p), t2(bar, p);
		
		p.reset(); // release ownership from main
		cout << "Shared ownership between 2 threads and released" << endl;
		cout << "ownership from main" << endl;
		cout << "  p.get() = " << p.get() << ", p.use_count() = " << p.use_count() << endl;
		t1.join(); t2.join();
		cout << "All threads completed, the last one deleted Derived" << endl;

		cout << endl;
	}
};