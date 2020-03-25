#include <iostream>

#include "Sender.h"

int main() {
  Sender sender;
  Observer observer;
  sender.Register(&observer);
  sender.DoSomething();
  sender.Deregister(&observer);
  return 0;
}

