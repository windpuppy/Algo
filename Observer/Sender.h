#pragma once

#include "Notifier.h"

class Sender : public Notifier{
public:
  void DoSomething() {
    Notify();
  }
};
