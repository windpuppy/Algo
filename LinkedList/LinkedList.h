#pragma once

#include "../Common/Common.h"

#include <string>
#include <vector>
#include <ctime>
#include <queue>

using namespace std;

class NodeComparatorGreater {
public:
  bool operator()(ListNode* n1, ListNode* n2) {
    return n1->value > n2->value;
  }
};

class LinkedList
{
public:

  //        o----->o----->o----->o----->NULL
  // prev  curr   next
  // Move from left to right
  // Time: O(n)
  // Space: O(1)
  ListNode* reverse_iterative(ListNode* head) {
    // WE DO NOT NEED THIS
    //if (!head || !head->next)
    //  return head;

    auto prev = (ListNode*)NULL;
    auto curr = head;
    auto next = (ListNode*)NULL; // curr->next

    while (curr) {
      next = curr->next;
      curr->next = prev;

      prev = curr;
      curr = next;
    }
    return prev;
  }

  // Move from right to left
  // Time: O(n)
  // Space: O(n)
  ListNode* reverse_recursive(ListNode* head) {
    if (!head || !head->next)
      return head;

    auto newHead = reverse_recursive(head->next);
    head->next->next = head; // e.g. 3 ask 4 to point back to 3
    head->next = NULL; // e.g. 3 cutting tie with 4
    return newHead; // return 4 (all the way to top level as our new head)
  }

  // Time: O(n)
  // Space: O(1)
  ListNode* middleNode(ListNode* head) {
    if (!head || !head->next)
      return head;

    auto fast = head, slow = head;
    while (fast && fast->next) {
      fast = fast->next->next; // fast += 2;
      if (!fast) return slow; // if we remove this line, we return 3 out of [1234], instead of 2.
      slow = slow->next; // slow ++;
    }
    return slow;
  }

  // Time: O(n)
  // Space: O(1)
  bool hasCycle(ListNode* head) {
    if (!head || !head->next)
      return false;

    auto slow = head, fast = head;
    while (fast && fast->next) {
      fast = fast->next->next;
      slow = slow->next;

      if (!fast || !fast->next) // managed to reach the end? no cycle.
        return false;

      if (fast == slow) // cycle detected.
        return true;
    }

    return false;
  }

  // Note: input already sorted!
  // Time: O(n)
  // Space: O(1)
  ListNode* insert(ListNode* head, int value) {
    ListNode* newNode = new ListNode(value);
    ListNode* curr = head;

    // Empty or value is already the min
    if (curr == NULL || curr->value >= value) {
      newNode->next = curr;
      return newNode;
    }

    while (curr->next != NULL && curr->next->value < value) // No need for <= here, because insert 3 into [1, 3, 5] is [1, 3, 3, 5]
      curr = curr->next;

    newNode->next = curr->next;
    curr->next = newNode;
    return head;
  }

  ListNode* mergeTwoSortedLists(ListNode* one, ListNode* two) {
    if (!one) return two;
    else if (!two) return one;

    auto dummy = new ListNode(0);
    auto curr = dummy;

    // 谁小移谁
    // when both have values
    while (one && two) {
      if (one->value < two->value) {
        curr->next = one;
        one = one->next;
      }
      else {
        curr->next = two;
        two = two->next;
      }
      curr = curr->next;
    }

    // one or both run out - connect the remaining valid one
    if (one && !two) curr->next = one;
    else if (two && !one) curr->next = two;

    return dummy->next;
  }

  // Use min heap
  // Time: O(nklogk)
  ListNode* mergeKSortedLists(vector<ListNode*> list) {
    priority_queue<ListNode*, vector<ListNode*>, NodeComparatorGreater> minHeap;

    for (auto n : list)
      minHeap.push(n);

    auto dummy = new ListNode(0);
    auto curr = dummy;

    while (!minHeap.empty()) {
      curr->next = minHeap.top();
      minHeap.pop();
      if (curr->next->next)
        minHeap.push(curr->next->next);
      curr = curr->next;
    }
    return dummy->next;
  }

  // Add two numbers
  ListNode* addTwoNumbers(ListNode* a, ListNode* b) {
    auto dummy = new ListNode(0);
    auto curr = dummy;
    int val = 0;

    // if a: a has nodes left
    // if b: b has nodes left
    // additional check fo val: last digits can sum up to 10, we need to push an additional digit
    while (a || b || val) {
      if (a) { val += a->value; a = a->next; }
      if (b) { val += b->value; b = b->next; }

      curr->next = new ListNode(val % 10);
      val = val / 10; // 下一步进位
      curr = curr->next;
    }
    return dummy->next;
  }


  // Find mid and split, O(n)
  // Reverse 2nd, O(n/2)
  // Compare, O(n/2)
  // Time: O(n)
  bool isPalindrome(ListNode* head) {
    if (!head || !head->next) return true;

    auto mid = middleNode(head);
    auto right = reverse_iterative(mid->next);
    mid->next = 0;

    // checking right is enough, because left length either == right or == right + 1
    while (right) {
      if (head->value != right->value) return false;
      head = head->next;
      right = right->next;
    }
    return true;
  }

  // two pointers, prev and curr.
  // prev start with dummy, curr start with dummy->next
  // Time complexity: O(n)
  ListNode* removeElements(ListNode* head, int val) {
    ListNode* dummy = new ListNode(0);
    dummy->next = head;
    auto prev = dummy;
    auto curr = head;

    while (curr) {
      if (curr->value == val) {
        prev->next = curr->next;
        curr = curr->next;
      }
      else {
        prev = prev->next;
        curr = curr->next;
      }
    }
    return dummy->next;
  }

  // Split into two, reverse second, then pick (very similar to Palindrome)
  // 1) split the two - find mid, O(n)
  // 2) reverse 2nd, O(n/2)
  // 3) merge two together, O(n)
  // Time: O(n)
  ListNode* reorder(ListNode* head) {
    if (!head || !head->next || !head->next->next)
      return head;

    // 1) split the two
    auto mid = middleNode(head);
    auto two = mid->next;
    mid->next = NULL; // break the two
    auto one = head;

    // 2) reverse 2nd
    two = reverse_iterative(two);

    // 3) merge the two
    auto dummy = new ListNode(0);
    auto curr = dummy;
    while (two) { // only check p2 here, because p2 <= p1 (equal if input even, p1 = p2 + 1  if input odd)
      curr->next = one;
      one = one->next;
      curr = curr->next;

      curr->next = two;
      two = two->next;
      curr = curr->next;
    }
    // p1 might have one extra left (if input is odd)
    if (one)
      curr->next = one;

    return dummy->next;
  }

  // user two dummies, then combine them at the end
  // Time: O(n)
  // Space: O(1)
  ListNode* partition(ListNode* head, int target) {
    if (!head || !head->next) return head;

    auto dummySmall = new ListNode(0);
    auto dummyLarge = new ListNode(0);
    auto p1 = dummySmall;
    auto p2 = dummyLarge;
    auto curr = head;

    while (curr) {
      if (curr->value < target) {
        p1->next = curr;
        p1 = p1->next;
      }
      else {
        p2->next = curr;
        p2 = p2->next;
      }
      curr = curr->next;
    }

    // now p1 and p2 are pointing at the tail of dummySmall and dummyLarge, respectively
    p1->next = dummyLarge->next;
    p2->next = NULL; // clean tail
    return dummySmall->next;
  }

  ListNode* mergeSort(ListNode* head) {
    if (!head || !head->next) return head;

    // split into two
    auto mid = middleNode(head);
    auto midNext = mid->next;
    mid->next = NULL;

    // merge left and right
    auto left = mergeSort(head);
    auto right = mergeSort(midNext);
    return mergeTwoSortedLists(left, right);
  }


  // 1) Fast move n positions
  // 2) slow and fast both move, when fast == null, slow stops
  // 3) slow->next is the one to delete
  ListNode* removeNthFromEnd(ListNode* head, int n) {
    auto slow = head;
    auto fast = head;

    for (int i = 0; i < n; ++i) {
      // reached the end? it depends
      // if n == length of LL, we delete the head
      if (!fast->next) {
        if (i == n - 1)
          head = head->next;
        return head;
      }
      fast = fast->next;
    }

    while (fast->next) {
      slow = slow->next;
      fast = fast->next;
    }

    if (slow->next)
      slow->next = slow->next->next;
    return head;
  }


  // Recursion: split a bigger problem into a smaller one
  // 1 --> 2 --> 3 --> 4 --> 5 --> 6
  // 1     2  |  3 --> 4 --> 5 --> 6
  // |     |
  // h     nh
  // here we need to swap 1 and 2, and also:
  // h.next = recursionFunction(3)
  // nh.next = h
  // return nh
  ListNode* reverseInPairs(ListNode* head) {
    if (!head || !head->next) return head;

    auto newHead = head->next;
    head->next = reverseInPairs(head->next->next);
    newHead->next = head;
    return newHead;
  }

  ListNode* removeDuplicatesFromSorted(ListNode* head) {
    if (!head || !head->next)
      return head;

    auto curr = head;
    while (curr && curr->next) {
      if (curr->value == curr->next->value)
        curr->next = curr->next->next;
      else
        curr = curr->next;
    }
    return head;
  }



  // Input: 1->1->1->2->3
  // Output: 2->3
  ListNode* removeAllDuplicates(ListNode* head) {
    if (!head || !head->next)
      return head;

    auto dummy = new ListNode(0);
    dummy->next = head;

    auto slow = dummy;
    auto fast = head;

    while (fast) {
      while (fast->next && slow->next->value == fast->next->value)
        fast = fast->next;

      // jump happened above? (if not, slow and fast should be next to each other)
      if (slow->next == fast) slow = fast;
      else slow->next = fast->next;

      fast = fast->next;
    }

    return dummy->next;
  }




  // 1. insert new nodes in a "sandwiched" fashion: A-a-B-b-C-c-D-d
  // 2. A.next.random = A.random.next
  // 3. separate ABCD and abcd
  // // Time O(n), Space O(1)
  RandomListNode* deepCopyLinkedListRandomPointer(RandomListNode* head) {
    // 1. insert sandwiched fashion
    auto curr = head;
    while (curr) {
      auto temp = curr->next;
      curr->next = new RandomListNode(curr->value);
      curr->next->next = temp;
      curr = temp;
    }

    // 2. hook up random nodes
    curr = head;
    while (curr) {
      if (curr->next)
        curr->next->random = curr->random ? curr->random->next : NULL; // random could be null
      curr = curr->next ? curr->next->next : NULL; // move by 2
    }

    // 3. separate
    curr = head;
    auto newHead = curr->next;
    auto curr2 = newHead;
    while (curr && curr2) {
      curr->next = curr->next ? curr->next->next : NULL; // original list
      curr2->next = curr2->next ? curr2->next->next : NULL; // new list
      curr = curr->next;
      curr2 = curr2->next;
    }

    return newHead;
  }
};






