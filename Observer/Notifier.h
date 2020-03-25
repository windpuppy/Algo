#pragma once

#include "Observer.h"
#include <algorithm>

using namespace std;

class Notifier {
public:
  virtual void Register(IObserver* o) {
    observers_.insert(o);
    cout << "Observer registered." << endl;
  }

  virtual void Deregister(IObserver* o) {
    if (observers_.count(o)) {
      observers_.erase(o);
      cout << "Observer deregistered." << endl;
    }
    else {
      cout << "Could not deregister an observer that is not registered." << endl;
    }
  }

protected:
  virtual void Notify() {
    auto notification = [&](IObserver* o) {
      o->HandleNotification();
    };

    for_each(observers_.begin(), observers_.end(), notification);
  }

private:
  set<IObserver*> observers_;
};
