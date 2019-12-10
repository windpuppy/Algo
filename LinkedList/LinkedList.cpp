#include "LinkedList.h"

int main()
{
  LinkedList sol;

  // Reverse linked list - iteratively
  {
    auto test = new ListNode(0);
    test = Helper::build_linked_list(test, 0, 1000);
    clock_t t = clock();
    for(int n = 0; n < 100; ++n)
      test = sol.reverse_iterative(test);
    t = clock() - t;
    printf("It took me %d clicks (%f seconds).\n", t, t / (double)CLOCKS_PER_SEC);
  }

  // Reverse linked list - recursively
  {
    auto test = new ListNode(0);
    test = Helper::build_linked_list(test, 0, 1000);
    clock_t t = clock();
    for (int n = 0; n < 100; ++n)
      test = sol.reverse_recursive(test);
    t = clock() - t;
    printf("It took me %d clicks (%f seconds).\n", t, t / (double)CLOCKS_PER_SEC);
  }

  // Reverse linked list - iteratively
  {
    auto head = Helper::string_to_listNode("1234");
    Helper::print_node(head);
    head = sol.reverse_iterative(head);
    Helper::print_node(head);
  }

  // Reverse linked list - recursively
  {
    auto head = Helper::string_to_listNode("1234");
    Helper::print_node(head);
    head = sol.reverse_recursive(head);
    Helper::print_node(head);
  }

  // Middle node
  {
    auto head = Helper::string_to_listNode("543210");
    Helper::print_node(head);
    head = sol.middleNode(head);
    Helper::print_node(head);
  }

  // Has cycle
  {
    auto head = Helper::string_to_listNode("1");
    auto res = sol.hasCycle(head);
    head = Helper::string_to_listNode("11");
    res = sol.hasCycle(head);
    head = Helper::string_to_listNode("111");
    res = sol.hasCycle(head);
  }

  // Insert in a sorted linked list
  {
    auto head = Helper::string_to_listNode("135");
    auto res = sol.insert(head, 2);
    Helper::print_node(res);
    res = sol.insert(head, 3);
    Helper::print_node(res);
    head = Helper::string_to_listNode("23");
    res = sol.insert(head, 1);
    Helper::print_node(res);
    head = Helper::string_to_listNode("23");
    res = sol.insert(head, 4);
    Helper::print_node(res);
  }

  // ReOrder linked list
  {
    auto array = Helper::string_to_listNode("12345678");
    auto res = sol.reorder(array);
    Helper::print_node(res);
    array = Helper::string_to_listNode("1234567");
    res = sol.reorder(array);
    Helper::print_node(res);
  }

  // Partition linked list
  {
    auto array = Helper::string_to_listNode("24351");
    auto res = sol.partition(array, 3);
    Helper::print_node(res); // 21435
  }

  // Merge sort linked list
  {
    auto head = Helper::string_to_listNode("25387910");
    auto res = sol.mergeSort(head);
    Helper::print_node(res);
  }

  // Merge two sorted linked lists
  {
    auto one = Helper::string_to_listNode("05558");
    auto two = Helper::string_to_listNode("234457");
    auto res = sol.mergeTwoSortedLists(one, two);
    Helper::print_node(res);
  }

  // Merge K sorted linked lists
  {
    auto one = Helper::string_to_listNode("1357");
    auto two = Helper::string_to_listNode("2468");
    auto thr = Helper::string_to_listNode("09");
    vector<ListNode*> list{ one, two, thr };
    auto res = sol.mergeKSortedLists(list);
  }

  // Add two numbers
  {
    auto a = Helper::string_to_listNode("98"); // number 89
    auto b = Helper::string_to_listNode("11"); // number 11
    auto res = sol.addTwoNumbers(a, b);
    Helper::print_node(res); // number 100, but printed as [0, 0, 1]
    a = Helper::string_to_listNode("243"); // number 342
    b = Helper::string_to_listNode("564"); // number 465
    res = sol.addTwoNumbers(a, b);
    Helper::print_node(res); // number 807, but printed as [7, 0, 8]
  }

  // Check linked list is Palindrome
  {
    auto array = Helper::string_to_listNode("123421");
    auto res = sol.isPalindrome(array); // false
    array = Helper::string_to_listNode("12321");
    res = sol.isPalindrome(array); // true
    array = Helper::string_to_listNode("1221");
    res = sol.isPalindrome(array); // true
  }

  // Remove linked list elements
  {
    auto array = Helper::string_to_listNode("1263456");
    auto res = sol.removeElements(array, 6); // 12345
    Helper::print_node(res);
  }

  // Remove nth node from end
  {
    auto head = Helper::string_to_listNode("123");
    auto res = sol.removeNthFromEnd(head, 1);

    head = Helper::string_to_listNode("12345");
    res = sol.removeNthFromEnd(head, 5);

    head = Helper::string_to_listNode("12345");
    res = sol.removeNthFromEnd(head, 800);
  }

  // Reverse in pairs
  {
    auto head = Helper::string_to_listNode("1234");
    auto res = sol.reverseInPairs(head);
    Helper::print_node(res);

    head = Helper::string_to_listNode("123");
    res = sol.reverseInPairs(head);
    Helper::print_node(res);
  }

  // Remove duplicates / all duplicates
  {
    auto head = Helper::string_to_listNode("1223");
    auto res = sol.removeDuplicatesFromSorted(head);

    head = Helper::string_to_listNode("1223");
    res = sol.removeAllDuplicates(head);
    head = Helper::string_to_listNode("122");
    res = sol.removeAllDuplicates(head);
    head = Helper::string_to_listNode("111");
    res = sol.removeAllDuplicates(head);
  }

  cin.get();
  
  return 0;
}
