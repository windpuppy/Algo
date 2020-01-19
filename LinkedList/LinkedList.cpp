#include "LinkedList.h"
#include "../Common//ListHelper.h"

int main()
{
  LinkedList sol;

  // Reverse linked list - iteratively
  {
    auto test = new ListNode(0);
    test = ListHelper::build_linked_list(test, 0, 1000);
    clock_t t = clock();
    for(int n = 0; n < 100; ++n)
      test = sol.reverse_iterative(test);
    t = clock() - t;
    printf("It took me %d clicks (%f seconds).\n", t, t / (double)CLOCKS_PER_SEC);
  }

  // Reverse linked list - recursively
  {
    auto test = new ListNode(0);
    test = ListHelper::build_linked_list(test, 0, 1000);
    clock_t t = clock();
    for (int n = 0; n < 100; ++n)
      test = sol.reverse_recursive(test);
    t = clock() - t;
    printf("It took me %d clicks (%f seconds).\n", t, t / (double)CLOCKS_PER_SEC);
  }

  // Reverse linked list - iteratively
  {
    auto head = ListHelper::string_to_listNode("1234");
    ListHelper::print_node(head);
    head = sol.reverse_iterative(head);
    ListHelper::print_node(head);
  }

  // Reverse linked list - recursively
  {
    auto head = ListHelper::string_to_listNode("1234");
    ListHelper::print_node(head);
    head = sol.reverse_recursive(head);
    ListHelper::print_node(head);
  }

  // Middle node
  {
    auto head = ListHelper::string_to_listNode("543210");
    ListHelper::print_node(head);
    head = sol.middleNode(head);
    ListHelper::print_node(head);
  }

  // Has cycle
  {
    auto head = ListHelper::string_to_listNode("1");
    auto res = sol.hasCycle(head);
    head = ListHelper::string_to_listNode("11");
    res = sol.hasCycle(head);
    head = ListHelper::string_to_listNode("111");
    res = sol.hasCycle(head);
  }

  // Insert in a sorted linked list
  {
    auto head = ListHelper::string_to_listNode("135");
    auto res = sol.insert(head, 2);
    ListHelper::print_node(res);
    res = sol.insert(head, 3);
    ListHelper::print_node(res);
    head = ListHelper::string_to_listNode("23");
    res = sol.insert(head, 1);
    ListHelper::print_node(res);
    head = ListHelper::string_to_listNode("23");
    res = sol.insert(head, 4);
    ListHelper::print_node(res);
  }

  // ReOrder linked list
  {
    auto array = ListHelper::string_to_listNode("12345678");
    auto res = sol.reorder(array);
    ListHelper::print_node(res);
    array = ListHelper::string_to_listNode("1234567");
    res = sol.reorder(array);
    ListHelper::print_node(res);
  }

  // Partition linked list
  {
    auto array = ListHelper::string_to_listNode("24351");
    auto res = sol.partition(array, 3);
    ListHelper::print_node(res); // 21435
  }

  // Merge sort linked list
  {
    auto head = ListHelper::string_to_listNode("25387910");
    auto res = sol.mergeSort(head);
    ListHelper::print_node(res);
  }

  // Merge two sorted linked lists
  {
    auto one = ListHelper::string_to_listNode("05558");
    auto two = ListHelper::string_to_listNode("234457");
    auto res = sol.mergeTwoSortedLists(one, two);
    ListHelper::print_node(res);
  }

  // Merge K sorted linked lists
  {
    auto one = ListHelper::string_to_listNode("1357");
    auto two = ListHelper::string_to_listNode("2468");
    auto thr = ListHelper::string_to_listNode("09");
    vector<ListNode*> list{ one, two, thr };
    auto res = sol.mergeKSortedLists(list);
  }

  // Add two numbers
  {
    auto a = ListHelper::string_to_listNode("98"); // number 89
    auto b = ListHelper::string_to_listNode("11"); // number 11
    auto res = sol.addTwoNumbers(a, b);
    ListHelper::print_node(res); // number 100, but printed as [0, 0, 1]
    a = ListHelper::string_to_listNode("243"); // number 342
    b = ListHelper::string_to_listNode("564"); // number 465
    res = sol.addTwoNumbers(a, b);
    ListHelper::print_node(res); // number 807, but printed as [7, 0, 8]
  }

  // Check linked list is Palindrome
  {
    auto array = ListHelper::string_to_listNode("123421");
    auto res = sol.isPalindrome(array); // false
    array = ListHelper::string_to_listNode("12321");
    res = sol.isPalindrome(array); // true
    array = ListHelper::string_to_listNode("1221");
    res = sol.isPalindrome(array); // true
  }

  // Remove linked list elements
  {
    auto array = ListHelper::string_to_listNode("1263456");
    auto res = sol.removeElements(array, 6); // 12345
    ListHelper::print_node(res);
  }

  // Remove nth node from end
  {
    auto head = ListHelper::string_to_listNode("123");
    auto res = sol.removeNthFromEnd(head, 1);

    head = ListHelper::string_to_listNode("12345");
    res = sol.removeNthFromEnd(head, 5);

    head = ListHelper::string_to_listNode("12345");
    res = sol.removeNthFromEnd(head, 800);
  }

  // Reverse in pairs
  {
    auto head = ListHelper::string_to_listNode("1234");
    auto res = sol.reverseInPairs(head);
    ListHelper::print_node(res);

    head = ListHelper::string_to_listNode("123");
    res = sol.reverseInPairs(head);
    ListHelper::print_node(res);
  }

  // Remove duplicates / all duplicates
  {
    auto head = ListHelper::string_to_listNode("1223");
    auto res = sol.removeDuplicatesFromSorted(head);

    head = ListHelper::string_to_listNode("1223");
    res = sol.removeAllDuplicates(head);
    head = ListHelper::string_to_listNode("122");
    res = sol.removeAllDuplicates(head);
    head = ListHelper::string_to_listNode("111");
    res = sol.removeAllDuplicates(head);
  }

  cin.get();
  
  return 0;
}
