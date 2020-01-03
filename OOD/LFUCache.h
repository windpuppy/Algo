#pragma once

#include <list>

using namespace std;

// Design LFU cache, which supports both get() and set() with O(1) time
// Note: 1. every get should increase the frequency of this key
//       2. when removing the least frequent used key and multiple keys have the same frequency - use LRU as tie breaker
//
// Implementation:
//
// head --- 1 --- 3 --- 5      frequencies
//          |     |     |
//        (2,3) (4,3) (1,2)   (key,value) pair
//                |
//              (3,7)
// Vertically, we call each node LRUNode, which contains list<pair<int,int>>, list of key-value pair
// Horizontally, we store a list<LRUNode>
// both directions are doubly linked list (that's how C++ STL implements list)
// Then we user a global unordered_map<int, pair<Iit, Jit>>, where int is key, Iit and Jit are iterators along both directions
//    with this hashmap, we gain global control of all keys

