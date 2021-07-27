#include "LRUCache.h"
#include "LRUCacheInt.h"
#include "LFUCache.h"
#include "Codec.h"
#include "AutoComplete.h"
#include "RandomizedSet.h"
#include "FirstNonRepeating.h"

#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <cassert>
#include <algorithm>
#include <unordered_map>
#include <thread>

using namespace std;

class IPrintable {
public:
	virtual void print() = 0;
};

class Base {
	virtual void init() = 0;
};

class Parent : public Base, public IPrintable
{
	int a;
	int b;
public:
	Parent(int a, int b) : a(a), b(b) {
		cout << "Parent created." << endl;
	};

	virtual ~Parent() {
		cout << "Parent destroyed." << endl;
	}

	virtual void print() {
		cout << "Parent printed." << endl;
	}

	virtual void init() {};
};

class Child : public Parent
{
public:
	Child(int a, int b) : Parent(a, b) {
		cout << "Child created." << endl;
	};

	virtual ~Child() {
		cout << "Child destroyed." << endl;
	}

	virtual void print() override { // use override to be safe to cover the same signature
		cout << "Child printed." << endl;
	}

	//virtual void print(string s) override {} // compile error
};


//class Singleton {
//protected:
//  static Singleton* instance;
//  Singleton() {}
//public:
//  static Singleton* getInstance() {
//    return instance == NULL ? instance : new Singleton();
//  }
//  ~Singleton() {}
//};

enum Day {
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday
};



void print_hello_1() {
	cout << "hello 1" << endl;
}

int main()
{
	// Randomized set ---------------------------------------------------------
	{
		RandomizedSet set;
		set.insert(1);
		set.remove(2);
		set.insert(2);
		int v = set.getRandom();
		set.remove(1);
		set.insert(2);
		v = set.getRandom();
	}

	// First non-repeating ----------------------------------------------------
	{
		FirstNonRepeating fnr;
		fnr.read('a');
		char c = fnr.firstNonRepeating();
		fnr.read('b');
		c = fnr.firstNonRepeating();
		fnr.read('c');
		c = fnr.firstNonRepeating();
		fnr.read('a');
		c = fnr.firstNonRepeating();
		fnr.read('c');
		c = fnr.firstNonRepeating();
		fnr.read('c');
		c = fnr.firstNonRepeating();
		fnr.read('b');
		c = fnr.firstNonRepeating();
	}

	// Auto complete ----------------------------------------------------------
	{
		vector<string> sentences{ "i love you", "island", "iroman", "i love leetcode" };
		vector<int> times{ 5, 3, 2, 2 };
		AutoComplete ac(sentences, times);
		auto s1 = ac.input('i');
		auto s2 = ac.input(' ');
		auto s3 = ac.input('a');
		auto s4 = ac.input('#');
	}

	// LFU Cache --------------------------------------------------------------
	{
		int val = 0;

		LFUCache cache(2);
		cache.put(1, 1);
		cache.put(2, 2);
		val = cache.get(1);
		cache.put(3, 3);
		val = cache.get(2);
		val = cache.get(3);
		cache.put(4, 4);
		cache.get(1);
		cache.get(3);
		cache.get(4);
	}

	// Inheritence --------------------------------------------------------------
	{
		Parent* parent = new Parent(1, 2);
		parent->print();
		delete parent;
	}

	{
		Parent* parent = new Child(1, 2); // upcasting
		parent->print();
		delete parent;
	}

	{
		Child* child = new Child(1, 2);
		child->print();
		delete child;
	}

	{
		try {
			IPrintable* parent = new Parent(1, 2);
			parent->print();
			//delete parent; // runtime error
		}
		catch (exception& e) {
			cout << "Exception: " << e.what() << endl;
		}
	}

	{
		IPrintable* child = new Child(1, 2);
		child->print();
		//delete child; // runtime error
	}

	// Try catch throw --------------------------------------------------------------

	try {
		//assert(false); // cannot do that
	}
	catch (exception& e) {
		cout << "Exception: " << e.what() << endl;
	}

	try {
		int* a = new int[10];
		auto b = a[11];
		cout << b << endl; // crazy number!

		vector<char> c(10, 'c');
		//auto d = c[11];
		//cout << d << endl; // will crash, uncatchable

		int x = 0;
		int y = 10;
		//int z = y / x; // uncatchable
	}
	catch (...) {
		cout << "Will not reach here." << endl;
	}

	try {
		int x = 0;
		int y = 10;
		throw std::exception("example");
	}
	catch (exception& e) {
		cout << "Exception: " << e.what() << endl;
	}

	try {
		throw runtime_error("runtime error");
	}
	catch (runtime_error& e) {
		cout << "Exception: " << e.what() << endl;
	}

	// vector initilization -----------------------------------------------------------
	{
		vector<int> a; a.push_back(1); a.push_back(2);
		vector<char> b(2, 'c');
		vector<int> c{ 1, 2, 3 };
		vector<int> d(c.begin(), c.end());

		int arr[]{ 1, 2, 3 };
		int n = sizeof(arr) / sizeof(arr[0]);
		vector<int> e(arr, arr + n);

		Day day = (Day)1;
		Day day2 = (Day)7;
	}

	// Dedup --------------------------------------------------------------------------
	{
		vector<int> a{ 1 ,1, 2, 2, 3, 3 };
		auto b(a);
		auto it = std::unique(a.begin(), a.end());
		a.erase(it, a.end());
		it = std::unique(b.begin(), b.end());
		b.resize(distance(b.begin(), it));
	}

}

