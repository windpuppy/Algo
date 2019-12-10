// QueueStack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "StackByLinkedList.h"
#include "StackByQueues.h"
#include "QueueBy2Stacks.h"
#include "DequeBy3Stacks.h"
#include "SortWith2Stacks.h"
#include "StackWithMin.h"

int main()
{
  // Sort with 2 stacks (input + buffer)
  {
    SortWith2Stacks sol;
    stack<int> s1;
    s1.push(4);
    s1.push(1);
    s1.push(3);
    s1.push(1);
    s1.push(2);
    stack<int> s2;

    sol.sort2(s1, s2);
  }
  
  // Implement queue by 2 stacks
  {
    QueueBy2Stacks sol;
    sol.push(1);
    sol.push(2);
    sol.push(3);
    sol.push(4);

    sol.printStack(2);
    sol.push(8);
    sol.printStack(3);
  }

  // Enhance stack with min() function
  {
    StackWithMin sm;
    cout << sm.top() << endl;
    sm.pop();
    cout << sm.top() << endl;
    cout << sm.min() << endl;

    sm.push(1);
    cout << sm.top() << endl;
    cout << sm.min() << endl;

    sm.push(2);
    cout << sm.top() << endl;
    cout << sm.min() << endl;

    sm.push(3);
    cout << sm.top() << endl;
    cout << sm.min() << endl;

    sm.pop();
    cout << sm.top() << endl;
    cout << sm.min() << endl;
  }

  // Implement deque with 3 stacks
  {
    DequeBy3Stacks sol;
    for (int n = 4; n > 0; --n) sol.push_front(n);
    for (int n = 5; n <= 8; ++n) sol.push_back(n);

    cout << sol.front() << endl;
    sol.pop_front();
    cout << sol.back() << endl;
    sol.pop_back();

    sol.pop_back();
    sol.pop_back();
    sol.pop_back();
    sol.pop_back();

    cout << sol.front() << endl;
    cout << sol.back() << endl;
  }

  // Stack with linked list
  {
    StackByLinkedList sol;
    sol.push(0);
    sol.push(1);
    sol.push(2);
  }

  // Stack with queues
  {
    StackByQueues sol;
    bool isEmpty = sol.isEmpty();
    sol.push(1);
    isEmpty = sol.isEmpty();
    int* val = sol.pop();
    isEmpty = sol.isEmpty();
  }

  return 0;
}

