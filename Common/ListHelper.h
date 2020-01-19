#pragma once

#include "Common.h"
#include <vector>
#include <iostream>
#include <string>

using namespace std;

class ListHelper
{
public:
  static ListNode* build_linked_list(ListNode* node, int start, int end)
  {
    if (start > end) return node;
    ListNode* temp = node;

    while (start != end) {
      node->next = new ListNode(++start);
      node = node->next;
    }

    node->next = NULL;
    return temp;
  }

  static vector<int> string_to_vec(string input)
  {
    vector<int> output;
    for (auto s : input)
      output.push_back(s - '0');
    return output;
  }

  static ListNode* string_to_listNode(string input)
  {
    // Generate list from the input
    vector<int> list = string_to_vec(input);

    // Now convert that list into linked list
    ListNode* dummy = new ListNode(0);
    ListNode* ptr = dummy;
    for (int item : list) {
      ptr->next = new ListNode(item);
      ptr = ptr->next;
    }
    ptr = dummy->next;
    delete dummy;
    return ptr;
  }

  static void print_node(ListNode* node)
  {
    string out = listNode_to_string(node);
    cout << out << endl;
  }



private:

  static int string_to_int(string input) {
    return stoi(input);
  }

  static string listNode_to_string(ListNode* node) {
    if (node == NULL) {
      return "[]";
    }

    string result;
    while (node) {
      result += to_string(node->value) + ", ";
      node = node->next;
    }
    return "[" + result.substr(0, result.length() - 2) + "]";
  }
};

