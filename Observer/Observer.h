#pragma once

#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

class IObserver {
public:
  virtual void HandleNotification() = 0;
};

class Observer : public IObserver {
public:
  Observer() :number_(0) {};

private:
  virtual void HandleNotification() {
    cout << "The observer is notified " << ++number_ << " times." << endl;
  }
private:
  int number_;
};
