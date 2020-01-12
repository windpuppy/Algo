#pragma once

#include <iostream>

#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <string>
#include <queue>
#include <stack>

using namespace std;

const int MAGIC_NUMBER = 26;

bool StringLengthComparator(const string& s1, const string& s2) {
  return s1.size() < s2.size();
}


class HashString {

  // max heap
  class PairComparatorLess {
  public:
    bool operator()(pair<string, int> p1, pair<string, int> p2) {
      // small improvement: if same frequency, word with lower alphabetical order goes first
      return p1.second == p2.second ? p1.first > p2.first : p1.second < p2.second;
    }
  };

  // point(x, y), sort the points by x ascending and y descending
  class SlopeComparator {
  public:
    bool operator()(pair<int, int> p1, pair<int, int> p2) {
      return p1.first != p2.first ? p1.first < p2.first : p2.second < p1.second;
    }
  };

  
public:
  // O(n) + O(nlogn) + O(klogn)
  vector<string> topKFrequentWords(vector<string> input, int k) {
    // step 1: build map, O(n)
    unordered_map<string, int> map;
    for (auto const& n : input)
      map[n]++;

    // step 2: PQ, O(nlogn)
    priority_queue<pair<string, int>, vector<pair<string, int>>, PairComparatorLess> pq;
    for (auto const& n : map)
      pq.push({ n.first, n.second });

    // step 3: pop k, O(klogn)
    vector<string> result;
    for (int n = 0; n < k; ++n) {
      if (pq.empty()) break;
      result.push_back(pq.top().first);
      pq.pop();
    }
    return result;
  }

  // assumption: input sorted, only 1 missing
  // method 1: hash 3, 1, 4; then from 1-4, check hash
  // method 2: vector<bool> seen, 3, 1, 4 all true, missing 4
  // method 3: sum of 1-n, sum of input, minus the two
  // method 4: bit operation
  int missingNumber(vector<int> nums) {
    if (nums.empty()) return 1;
    int n = nums.size() + 1;
    int res = 0;
    for (int i = 0; i <= n; ++i) res ^= i; // xor 1 to n
    for (auto i : nums) res ^= i; // xor input
    return res;
  }

  vector<int> commonNumbers(vector<int> a, vector<int> b) {
    vector<int> res;
    int i = 0, j = 0;
    while (i < a.size() && j < b.size())
      if (a[i] == b[j]) {
        res.push_back(a[i++]);
        j++;
      }
      else if (a[i] < b[j])
        i++;
      else
        j++;

    return res;
  }

  // Lets try in-place
  string removeCertainCharacters(string input, string t) {
    if (input.empty() || t.empty()) return input;
    unordered_set<char> set(t.begin(), t.end());

    // slow faster pointers
    int slow = 0;
    for (int fast = slow; fast < input.size(); ++fast)
      if (set.find(input[fast]) == set.end())
        input[slow++] = input[fast];

    return input.substr(0, slow);
  }

  // Do it in-place
  string removeSpaces(string input) {
    if (input.empty()) return input;
    char space(' ');

    int slow = 0;
    for (int fast = 0; fast < input.size(); ++fast) {
      // skip spaces if 1) at begining, or 2) repeating space
      if (input[fast] == space && (fast == 0 || input[fast - 1] == space))
        continue;
      input[slow++] = input[fast]; // end <= i is guaranteed, so no worries on overwriting
    }

    // trim useless part
    input = input.substr(0, slow);

    // can still contain one space at the end
    if (input.back() == space)
      input.pop_back();

    return input;
  }

  // Simple, one pass dedup
  string removeAdjacentRepeatedChars(string input) {
    if (input.empty() || input.size() == 1) return input;

    int slow = 1;
    for (int fast = 1; fast < input.size(); ++fast) {
      if (input[fast] != input[slow - 1])
        input[slow++] = input[fast];
    }

    return input.substr(0, slow);
  }

  // Recursive dedup
  // Use a stack
  string removeAdjacentRepeatedCharsIV(string input) {
    if (input.empty() || input.size() == 1) return input;
    int size = input.size();
    deque<char> stack;
    stack.push_back(input.front());
    for (int n = 1; n < input.size(); ++n) {
      // if not equal, keep pushing
      if (stack.empty() || input[n] != stack.back()) {
        stack.push_back(input[n]);
      }
      else if (input[n] == stack.back()) {
        stack.pop_back();

        // continue to dedup
        while (n < size - 1 && input[n + 1] == input[n])
          n++;
      }
    }

    string res;
    while (!stack.empty()) {
      res += stack.front();
      stack.pop_front();
    }
    return res;
  }

  int isSubstring(string large, string small) {
    if (large.size() < small.size()) return -1;
    if (small.empty()) return 0;

    for (int i = 0; i < large.size() - (int)small.size() + 1; ++i) {
      if (areEqualAt(large, i, small))
        return i;
    }
    return -1;
  }

  // Compare small with large at n
  bool areEqualAt(string large, int n, string small) {
    for (int i = 0; i < small.size(); ++i)
      if (large[i + n] != small[i])
        return false;
    return true;
  }



  int isSubstring_RabinKarp(string large, string small) {
    if (large.size() < small.size()) return -1;
    if (small.empty()) return 0;

    unsigned long long targetHash = getHashCode(small);

    int slow = 0;
    int fast = small.size() - 1;
    unsigned long long currHash = getHashCode(large, slow, fast);
    if (currHash == targetHash)
      return slow;

    for (fast = small.size(), slow = 1; fast < large.size(); fast++, slow++) {
      updateHashCode(large, slow, fast, currHash);
      if (currHash == targetHash)
        return slow;
    }
    return -1;
  }

  string reverseString(string input) {
    int i = 0, j = input.size() - 1;
    while (i < j)
      swap(input[i++], input[j--]);
    return input;
  }

  string reverseWords(string input) {
    if (input.empty() || input.size() == 1) return input;
    int size = input.size();

    // Step 1: reverse each words (using two pointers)
    int i = 0, j = 0;
    for (j = 0; j <= size; ++j) {
      if (input[j] == ' ' || j == size) {
        reverseSubstring(input, i, j - 1);
        i = j + 1;
        j++;
      }
    }

    // Step 2: reverse whole string
    reverseSubstring(input, 0, size - 1);
    return input;
  }

  void reverseSubstring(string& input, int i, int j) {
    while (i < j)
      swap(input[i++], input[j--]);
  }



  string rightShift(string input, int n) {
    if (input.empty() || input.size() == 0) return input;
    n %= input.size();
    reverse(input.begin(), input.end());
    reverse(input.begin(), input.begin() + n);
    reverse(input.begin() + n, input.end());
    return input;
  }

  string replace(string input, string s, string t) {
    return s.size() >= t.size()
      ? replaceShorter(input, s, t)
      : replaceLonger(input, s, t);
  }

  string replaceShorter(string input, string s, string t) {
    int size = input.size(), size1 = s.size(), size2 = t.size();

    // Slow: left of slow are all processed. When we do substring replacement, we do it at slow. At the end, slow will be out final output.
    // Fast: the faster pointer that looks for the matching and returns the char(s) need to be copied to the final output
    int slow = 0;
    int fast = 0;
    while (fast < size) {
      if (fast <= size - size1 && areEqualAt(input, fast, s)) {
        copySubstringAt(input, slow, t);
        slow += size2;
        fast += size1;
      }
      else
        input[slow++] = input[fast++];
    }

    return input.substr(0, slow);
  }

  string replaceLonger(string input, string s, string t) {
    int size = input.size(), size1 = s.size(), size2 = t.size();

    // Get all the matches first, get ready for input array allocation / expansion.
    auto matches = getAllMatches(input, s);
    if (matches.empty()) return input;
    int expandSize = matches.size() * (size2 - size1);
    input += string(expandSize, ' ');

    // Slow and fast both coming from right this time
    // Slow: traversing the new length
    // Fast: traversing the old length
    // Match index: going through the (previously found) matches
    int slow = size + expandSize - 1;
    int fast = size - 1;
    int matchIndex = matches.size() - 1;
    while (fast >= 0) {
      // Copy only if: matches not all processed, and when fast hit a match
      if (matchIndex >= 0 && fast == matches[matchIndex]) {
        copySubstringAt(input, slow - size2 + 1, t);
        slow -= size2;
        fast -= size1;
        matchIndex--;
      }
      else
        input[slow--] = input[fast--];
    }

    return input;
  }

  // Copy small into large at n
  void copySubstringAt(string& large, int n, string small) {
    for (int i = 0; i < small.size(); ++i)
      large[i + n] = small[i];
  }

  // Get all matches. Record end indexes for later convenience
  vector<int> getAllMatches(string large, string small) {
    vector<int> res;
    int size1 = large.size();
    int size2 = small.size();
    int i = 0;
    while (i <= size1) {
      if (areEqualAt(large, i, small)) {
        res.push_back(i + size2 - 1);
        i += size2;
      }
      else
        i++;
    }
    return res;
  }

  

  // Reorder string
  // In LL version, we use split (+ reverse 2nd) + combine method, but here we try to do it in place.
  // For ABCD1234 to make it A1B2C3D4
  // AB CD 12 34
  // AB 12 CD 34 (4 chunks, swap middle to chunks), then keep recursing
  // Here we use a more general case
  // ABC DEFG 123 4567
  //     |    |   |
  //     lm   m   rm
  // Work out the 3 boundaries, then call recursion as below:
  // swap chunk 2 and 3
  // reorder ABC123, reorder DEFG4567
  // so on...
  vector<int> reorderArray(vector<int> input) {
    if (input.size() % 2 == 0)
      reorder(input, 0, input.size() - 1);
    else
      reorder(input, 0, input.size() - 2); // odd size array? ignore the last element
    return input;
  }

  // ABC DEFG 123 4567
  //     |    |   |
  //     lm   m   rm
  void reorder(vector<int>& input, int left, int right) {
    int length = right - left + 1;

    // base case
    // <= 2? we are done.
    if (length <= 2)
      return;

    int mid = left + length / 2;
    int lm = left + length / 4;
    int rm = left + length * 3 / 4;

    int sizeChunk1 = lm - left;
    // ABC DEFG 123 4567
    reverse(input.begin() + lm, input.begin() + mid);   // ABC GFED 123 4567
    reverse(input.begin() + mid, input.begin() + rm);   // ABC GFED 321 4567
    reverse(input.begin() + lm, input.begin() + rm);    // ABC 123 DEFG 4567
                                                        //         |
                                                        //      new mid
    int newMid = left + sizeChunk1 * 2;
    reorder(input, left, newMid - 1);
    reorder(input, newMid, right);
  }



  // compress abbccc -> ab2c3, instead of a1b2c3
  string compress(string input) {
    if (input.empty() || input.size() == 1) return input;
    const int length = input.size();
    int newLength = 0;

    int slow = 0;
    int fast = 0;
    while (fast < length) {
      // pinpoint first char in each while loop
      int first = fast;
      fast++;
      while (fast < length && input[fast] == input[first])
        fast++;

      // copy first char
      input[slow++] = input[first];

      // repeating chars?
      int count = 0;
      if (fast - first > 1) {
        count = copyDigits(input, slow, fast - first);
        slow += count; // slow moves num digits (it can be a1, or it can be a12 if there are 12 'a's)
      }
      newLength += 1 + count; // char itself + num digits
    }

    input.resize(newLength);
    return input;
  }

  // copy n chars to slow position
  int copyDigits(string& input, int index, int count) {
    if (!count) return 0;
    auto str = to_string(count);
    for (int n = 0; n < str.size(); ++n) {
      input[index++] = str[n];
    }
    return (int)str.size();
  }



  // compress 2 : aaabbcdee -> a3b2c1d1e2
  // We run two passes
  // 1st pass - use slow and fast pointers, compress repeating chars
  // 2nd pass - move slow and fast backwards, append "1"s to unique chars
  string compress2(string input) {
    if (input.empty() || input.size() == 1) return input;
    int length = input.size();
    int newLength = 0; // newLength can be shorter than input length, so we start from zero and build it!

    // FIRST PASS ///////////////////////////////////////
    int slow = 0;
    int fast = 0;
    while (fast < length) {
      // pinpoint first char in each while loop
      int first = fast++;
      while (fast < length && input[fast] == input[first])
        fast++;

      // copy first char
      input[slow++] = input[first];

      // repeating chars?
      if (fast - first > 1) {
        int count = copyDigits(input, slow, fast - first);
        slow += count; // slow moves num digits (it can be a1, or it can be a12 if there are 12 'a's)
        newLength += 1 + count; // char itself + num digits
      }
      // unique chars
      else {
        newLength += 2;
      }
    }

    // SECOND PASS ///////////////////////////////////////
    // Now if input a a a b b c d e e
    // Processed:   a 3 b 2 c d e 2 
    //                              | |
    //                              s f
    // slow: right to tail of copied chars
    // fast: right to tail of input chars (pointing at empty)
    input.resize(newLength);

    fast = slow - 1; // pointing back to last char: 2
    slow = newLength - 1; // point at the tail of new length

    // reversed physical meaning:
    // right to the slow: chars copied
    // left to the fast (inclusive) to be processed
    // Processed:   a 3 b 2 c d e 2 _ _
    //                            |   |
    //                            f   s

    while (fast >= 0) {
      // copy digits
      if (isdigit(input[fast]))
        while (fast >= 0 && isdigit(input[fast]))
          input[slow--] = input[fast--];
      // copy chars
      else
        input[slow--] = '1';
      input[slow--] = input[fast--];
    }

    return input;
  }



  // Decompress abc2 -> abcc
  // Time: O(n)
  string decompress(string input) {
    if (input.empty()) return input;
    int shortSize = input.size(), longSize = input.size();
    for (auto c : input) {
      int d = c - '0';
      if (d > 0 && d <= 9)
        longSize += d - 2;
    }
    input.resize(longSize);

    int slow = longSize - 1;
    int fast = shortSize - 1;

    // we can skip fast == 0, because first char cannot be digit
    while (fast > 0) {
      int digit = input[fast] - '0';

      // process a2 and beyond
      if (digit >= 2 && digit <= 9) {
        for (int i = 0; i < digit; ++i)
          input[slow--] = input[fast - 1]; // copy 3 'd's
        fast -= 2;
      }
      // a0, a1, a2 already processed earlier
      else {
        input[slow--] = input[fast--];
      }
    }
    return input;
  }



  // Two passes
  // decompress short (a0, a1, a2), decompress long (a3 -> aaa)
  // Assumption given: no repeating chars > 9, ie. input won have like 'a10', so all digits are single
  string decompress2(string input) {
    if (input.empty()) return input;

    int shortSize = 0, longSize = 0;

    // input:            a 2 b 0 c 1 d 3 
    // after first pass: a a c d 3
    //                             |     |
    //                             s     f
    decompressShort(input, shortSize, longSize);
    input.resize(longSize);

    // at this point
    // shortSize = 5: the saved content SO FAR
    // longSize = 6: size of expected return (sum of all non-zero digits)
    decompressLong(input, shortSize, longSize);
    return input;
  }

  void decompressShort(string& input, int& shortSize, int& longSize) {
    int length = input.size();
    int slow = 0;
    int fast = 0;
    longSize = 0;

    while (fast < length) {

      int digit = input[fast + 1] - '0';

      // handle a0, a1, a2 first
      if (digit >= 0 && digit <= 2) {
        for (int j = 0; j < digit; ++j)
          input[slow++] = input[fast];
      }
      // if a3 and beyond, we handle them later
      else {
        input[slow++] = input[fast];
        input[slow++] = input[fast + 1];
      }

      // input format "a2b0c1d4"..., we can skip by 2 with confidence
      fast += 2;
      longSize += digit;
    }

    shortSize = slow;
  }

  void decompressLong(string& input, int shortSize, int longSize) {
    // input:            a 2 b 0 c 1 d 3 
    // after first pass: a a c d 3 _
    //                           | |
    //                           f s
    int slow = longSize - 1;
    int fast = shortSize - 1;

    // we can skip fast == 0, because first char cannot be digit
    while (fast > 0) {
      int digit = input[fast] - '0';

      // process a3 and beyond
      if (digit > 2 && digit <= 9) {
        for (int i = 0; i < digit; ++i)
          input[slow--] = input[fast - 1]; // copy 3 'd's
        fast -= 2;
      }
      // a0, a1, a2 already processed earlier
      else {
        input[slow--] = input[fast--];
      }
    }
  }



  // Encode space
  // This is essentially a "string replace longer" problem
  // We scan the string twice. First time, count spaces then expand string; Second time, replace them with "%20"
  string encodeSpace(string input) {
    if (input.empty()) return input;

    int count = 0;
    for (auto c : input)
      if (c == ' ') count++;
    if (count == 0) return input;

    // resize
    const int size = input.size();
    input += string(count * 2, ' ');
    const int newSize = input.size();

    int slow = size - 1;
    int fast = newSize - 1;
    while (slow >= 0) {
      if (input[slow] != ' ') {
        input[fast--] = input[slow];
      }
      else {
        input[fast--] = '%';
        input[fast--] = '0';
        input[fast--] = '2';
      }
      slow--;
    }
    return input;
  }



  // Use a set to record everything we've seen so far
  // Incoming char: if new: keep pushing fast (and update global max)
  //                if old: keep pushing slow
  int longestNoRepeat(string s) {
    if (s.empty()) return 0;
    else if (s.size() == 1) return 1;

    unordered_set<char> set;
    int slow = 0, fast = 0, longest = 0;

    while (fast < s.size()) {
      char curr = s[fast];

      if (set.find(curr) != set.end()) {
        set.erase(s[slow++]); // found? erase
      }
      else {
        set.insert(curr); // not found? insert
        fast++;

        longest = max(longest, fast - slow); // update longest: slow - fast is our new sliding window
      }
    }

    return longest;
  }

  // A more efficient solution:
  // Instead of using a set, we use map<char, lastOccurance>
  // For each incoming char, if 1) we find it in the map 2) its last occurance is inside the current sliding window (or otherwise we don't care)
  //     then we update the global max
  //     and we also pull current sliding window here
  int longestNoRepeat2(string s) {
    if (s.empty()) return 0;
    else if (s.size() == 1) return 1;

    int currStart = 0, maxStart = 0;
    int currlen = 0, maxlen = 0;

    // hash<char, lastOccurance>
    unordered_map<char, int> map;
    map[s[0]] = 0;

    int i;
    for (i = 1; i < s.length(); i++) {
      char c = s[i];

      // Only do this if:
      if (map.find(c) != map.end() && // 1) we have seen this before
          map[c] >= currStart) {      // 2) this happened inside the current substring (or otherwise we don't care)
        currlen = i - currStart;
        if (currlen > maxlen) { maxStart = currStart; maxlen = currlen; }

        // Next substring will NOT start from here, it starts after the previous occurrence of this char (ie. sliding window)
        currStart = map[c] + 1;
      }

      map[c] = i; // Update last occurrence of current character. 
    }

    // One more check for the last substring
    if (i - currStart > maxlen)
      maxlen = i - currStart;

    return maxlen;
  }


  // Given "cbaebabacd" and "abc", return starting indices of all anagrams of "abc" (0, 6 here)
  // Solution: sliding window with a map<char, count>, and a match counter
  //
  // Note: this solution is NOT Robin-Karp! You can consider this as a variation of it,
  //    but Robin-Karp re-computes the actual hash code of the sliding window everytime,
  //    and this solution does not (it only updates the HashMap based on the frequency change)
  vector<int> allAnagrams(string large, string small) {
    vector<int> res;
    if (large.empty() || large.size() < small.size()) return res;
    const int size1 = large.size();
    const int size2 = small.size();

    // e.g. nothing else other than chars in small string will goes into this map
    unordered_map<char, int> map;
    for (auto n : small) map[n]++;
    int match = 0;

    for (int i = 0; i < size1; ++i) {
      char curr = large[i];

      // 1) Process new char
      if (map.find(curr) != map.end()) {
        map[curr]--;
        if (map[curr] == 0) match++; // when char's count reduces to zero, we have 1+ match
      }

      // 2) Process old char going out of the sliding window
      if (i >= size2) {
        char old = large[i - size2];

        if (map.find(old) != map.end()) {
          map[old]++;
          if (map[old] == 1) match--; // when char's count goes from 0 to 1, we have 1- match
        }
      }

      // 3) Check current matching condition
      if (match == map.size())
        res.push_back(i - size2 + 1);
    }
    return res;
  }



  // Minimum length window that contains all chars in template t (chars can be in any order)
  // e.g. "adobecodebanc", "abc" ==> "banc" is the minimum window that contains "abc"
  // Use slow and fast pointers, we traverse all chars at most twice each
  // Time: O(n), Space: O(1) - the remain vector is fixed size 128
  string minimumWindowSubstring(string s, string t) {
    vector<int> remain(128, 0);
    for (auto c : t) remain[c]++; // remain chars to match in t
    int count = t.size(); // remain count of chars

    int slow = 0, fast = 0, minHead = 0, minLen = INT_MAX;

    while (fast < s.size()) {
      if (remain[s[fast++]]-- > 0) // explore fast
        count--;

      while (count == 0) { // we found a solution here!
        if (fast - slow < minLen) {
          minLen = fast - slow;
          minHead = slow;
        }

        if (remain[s[slow++]]++ == 0) // explore slow
          count++;
      }
    }
    return minLen == INT_MAX ? "" : s.substr(minHead, minLen);
  }



  string countAndSay(int n) {
    if (n == 0) return "";
    string res = "1";

    while (--n) {
      string cur = "";
      for (int i = 0; i < res.size(); i++) {
        int count = 1;
        while ((i < res.size() - 1) && (res[i] == res[i + 1])) {
          count++;
          i++;
        }

        cur += to_string(count) + res[i];
      }
      res = cur;
    }
    return res;
  }


  // intersection of two arrays
  vector<int> interset(vector<int> nums1, vector<int> nums2) {
    unordered_map<int, int> map1;
    for (auto n : nums1)
      map1[n]++;

    unordered_map<int, int> map2;
    for (auto n : nums2)
      map2[n]++;

    vector<int> res;
    for (auto n : map1) {
      if (map2.find(n.first) != map2.end()) {
        int numCommon = min(n.second, map2[n.first]);
        std::fill_n(back_inserter(res), numCommon, n.first);
      }
    }
    sort(res.begin(), res.end());
    return res;
  }



  // only consider 0-9 and case insensitive a-z, ignore the rest
  bool validPalindromeAlphaNumeric(string input) {
    if (input.empty() || input.size() == 1)
      return true;

    int i = 0;
    int j = input.size() - 1;

    while (i < j) {
      char a = input[i];
      char b = input[j];
      if (!isDigitOrChar(a))
        i++;
      else if (!isDigitOrChar(b))
        j--;
      else if (!areEqualCaseInsensitive(a, b))
        return false;
      else {
        i++;
        j--;
      }
    }
    return true;
  }

  bool isDigitOrChar(char a) {
    return isdigit(a) ||
      (a >= 'a' && a <= 'z') ||
      (a >= 'A' && a <= 'Z');
  }

  bool areEqualCaseInsensitive(char a, char b) {
    if (a == b)
      return true;

    if (a == b)
      return true;

    // need to do non-digit check on both
    // because 'P' - '0' = 32, and it will match 'a' - 'A'
    return (!isdigit(a) && !isdigit(b) &&
      (abs(a - b) == 'a' - 'A'));
  }



  // Input "abccccdd", output: 7
  int longestPalindrome(string s) {
    unordered_set<char> set;
    for (auto c : s)
      if (set.find(c) == set.end())
        set.insert(c);
      else
        set.erase(c);

    int setSize = set.size();
    int size = s.size();

    if (setSize <= 1)
      return size;
    else
      return size - setSize + 1;
  }

  // Solution:
  // a b | c f      e d | b a
  // In such case, we won't have a match either we delete c or d, return false
  // a b | c e    e c d | b a
  // In such case, we can delete d, then the rest will match
  bool validPalinedromeWithOneDelete(string s) {
    if (s.size() <= 2) return true;
    int i = 0;
    int j = s.size() - 1;

    while (i < j) {
      char a = s[i];
      char b = s[j];

      if (a == b) {
        i++;
        j--;
      }
      else {
        if (helper_palindrome(s, i + 1, j)) return true; // skip left char
        if (helper_palindrome(s, i, j - 1)) return true; // skip right char
        return false;
      }
    }
    return true;
  }

  // The most basic palindrome
  bool helper_palindrome(string input, int i, int j) {
    while (i < j) {
      if (input[i++] != input[j--])
        return false;
    }
    return true;
  }



  // Brutal force: check all substrings, run palindrome for each
  // That would be O(n^3)
  //
  // DP solution: use a 2D table
  // Do L = 1, L = 2, then L > 3 three passes
  // Time (O^2)
  // Space (O^2)
  //
  //       0 1 2 3 4
  //       a a b b a
  // 0 a | T T F F F
  // 1 a |   T F F T
  // 2 b |     T T F
  // 3 a |       T F
  // 4 a |         T
  string longestPalindromeSubstring(string str) {
    int n = str.size();
    vector<bool> tmp(n, false);
    vector<vector<bool>> table(n, tmp);

    // Update result on the go
    int maxLength = 1;
    int maxI = 0, maxJ = 0;

    // Fill L = 1
    for (int i = 0; i < n; ++i)
      table[i][i] = true;

    // Fill L = 2
    for (int i = 0; i < n - 1; ++i)
      if (str[i] == str[i + 1]) {
        table[i][i + 1] = true;
        maxLength = 2;
        maxI = i;
        maxJ = i + 1;
      }

    // Fill L > 2
    for (int offset = 2; offset <= n - 1; ++offset) {
      for (int i = 0; i < n - offset; ++i) {
        int j = i + offset;
        if (table[i + 1][j - 1] && str[i] == str[j]) {
          table[i][j] = true;
          maxLength = offset + 1;
          maxI = i;
          maxJ = j;
        }
      }
    }

    auto res = str.substr(maxI, maxJ - maxI + 1); // (start, length) NOT (start, end)
    return res;
  }



  // Similar to longest palindrome substring, we use DP to solve it with a 2D table
  // Instead of use True/False table, we use int table
  // For current cell, if str[i] == str[j], we fill it with its bottom-left cell's value + 2 (2 being the pair of i and j forming 2 extra length palindrome)
  //     we also update record
  //                   if str[i] != str[j], we fill it with max(its left, its right)
  // Time: O(n^2)
  // Space: O(n^2)
  //
  //       0 1 2 3 4 5
  //       a g b d b a
  // 0 a | 1 1 1 1 3 5
  // 1 g |   1 1 1 3 3
  // 2 b |     1 1 3 3
  // 3 d |       1 1 1
  // 4 b |         1 1
  // 5 a |           1
  // So longest palindrome subsequence is from 0 to 5 : "abdba"
  // We can also start from the top right corner, 5, and go bottom left direction to recover this string
  int longestPalindromeSubsequence(string str) {
    int n = str.size();
    vector<int> tmp(n, 0);
    vector<vector<int>> table(n, tmp);

    // Update result on the go
    int maxLength = 1;

    // Fill L = 1
    for (int i = 0; i < n; ++i)
      table[i][i] = 1;

    // Fill L = 2
    for (int i = 0; i < n - 1; ++i)
      if (str[i] == str[i + 1]) {
        table[i][i + 1] = 2;
        maxLength = 2;
      }
      else {
        table[i][i + 1] = 1;
      }

    // Fill L > 2
    for (int offset = 2; offset <= n - 1; ++offset) {
      for (int i = 0; i < n - offset; ++i) {
        int j = i + offset;

        if (str[i] == str[j]) { // Equa chars?
          table[i][j] = table[i + 1][j - 1] + 2;
          maxLength = max(maxLength, table[i][j]); // update result
        }
        else { // not equal chars
          table[i][j] = max(table[i][j - 1], table[i + 1][j]);
        }
      }
    }

    return maxLength;
  }



  // Exactly like the above Longest Palindrome substring
  // Just count the trues in this
  //       0 1 2 3 4
  //       a a b b a
  // 0 a | T T F F F
  // 1 a |   T F F T
  // 2 b |     T T F
  // 3 a |       T F
  // 4 a |         T
  //
  // DP solution:
  // Time (O^2)
  // Space (O^2)
  int countPalindromeSubstrings(string str) {
    const int n = str.size();
    vector<bool> tmp(n, false);
    vector<vector<bool>> table(n, tmp);

    // Count number of palindromes on the go
    int count = 0;

    // Fill L = 1
    for (int i = 0; i < n; ++i) {
      table[i][i] = true;
      count++;
    }

    // Fill L = 2
    for (int i = 0; i < n - 1; ++i)
      if (str[i] == str[i + 1]) {
        table[i][i + 1] = true;
        count++;
      }

    // Fill L > 2
    for (int offset = 2; offset <= n - 1; ++offset) {
      for (int i = 0; i < n - offset; ++i) {
        int j = i + offset;
        if (table[i + 1][j - 1] && str[i] == str[j]) {
          table[i][j] = true;
          count++;
        }
      }
    }

    return count;
  }

  

  // DP solution
  // Also similar to longest palindrome substring/subsequence, we use 2D table
  // Oppostie to the above problems, will try NOT to increase the table values as we scan it
  //
  //   a b c a
  // a 0 1 2 1
  // b   0 1 2
  // c     0 1
  // a       0
  int leastInsertionsToFormPalindrome(string str) {
    // "" considered palindrome already
    if (str.empty()) return 0;

    int n = str.size();
    vector<int> tmp(n, 0);
    vector<vector<int>> table(n, tmp);

    for (int offset = 1; offset < n; ++offset) {
      for (int i = 0; i < n - offset; ++i) {
        int j = i + offset;

        if (str[i] == str[j])
          table[i][j] = table[i + 1][j - 1]; //  same char? inherit bottom-left value
        else
          table[i][j] = min(table[i][j - 1], table[i + 1][j]) + 1; // min(left, right) + 1    - plus 1 because we have a new char to match
      }
    }

    return table[0][n - 1];
  }


  // Determine any permutation of the string can be a palindrome
  bool palindromePermutation(string str) {
    unordered_set<char> set;

    for (char n : str) {
      // not found? insert it
      if (set.find(n) == set.end())
        set.insert(n);
      // found? remove it.
      else
        set.erase(n);
    }

    return set.empty() || set.size() == 1;
  }



  // Use a stack
  // For all opening brackets, we push its closing counterpart - the one we are waiting to appear first next
  // For all closing brackets, we check if there is a conflict
  // The end stack should be empty!
  bool validParenthese(string s) {
    if (s.size() % 2 != 0)
      return false;

    stack<char> stack;
    for (auto c : s) {
      if (c == '(')
        stack.push(')');
      else if (c == '[')
        stack.push(']');
      else if (c == '{')
        stack.push('}');
      else if (stack.empty() || stack.top() != c)
        return false;
      else
        stack.pop();
    }

    return stack.empty();
  }

  

 
  // Clue: each int has 32bit, which is "enough" for our 26 characters, so we can use int to set the x-th bit of each character
  // For example, for "abcw", we set 0th, 1st, 2nd, 23rd bit, and stack them together with bit operation OR
  // 0000 0000 0100 0000 0000 0000 0000 0111 ==> "acbw" (but backwards)
  // Time: O(n^2)
  // Space: O(1)
  int largestProductOfLength(vector<string> words) {
    if (words.empty()) return 0;
    sort(words.begin(), words.end(), StringLengthComparator);
    vector<int> wordBits(words.size(), 0);
    int res = 0;

    for (int i = 0; i < words.size(); ++i) {
      string wi = words[i];

      for (auto c : wi)
        wordBits[i] |= 1 << (c - 'a');

      for (int j = i - 1; j >= 0; j--) {
        string wj = words[j];

        if ((wordBits[j] & wordBits[i]) == false) {
          res = max(res, (int)(wi.size() * wj.size()));
        }
      }
    }
    return res;
  }



  // Given a set of points, find the most points that form a single 2D line
  // Naive solution: 2 for loops to try each pair of points, then a 3rd for loop to try the remaining points
  // Time: O(n^3)
  // Better soluiton: use hashmap
  // Hashmap, key: <a, b>, value: a list of points
  // for for each pair of points pi and pj
  //    calculate y = ax + b, insert pi and pj
  // need to use a second hashmap for vertical lines, ie x = a
  // Time: O(n^2)
  int mostPointsOnALine(vector<pair<int, int>> points) {
    if (points.empty()) return 0;
    int res = 0;
    for (int i = 0; i < points.size(); ++i) {
      int same = 1; // for dedup
      int vert = 0; // treat vertical lines as special case (infinite slope)
      int most = 0;
      unordered_map<double, int> map;
      auto pi = points[i];

      for (int j = 0; j < points.size(); ++j) {
        if (i == j) continue;
        auto pj = points[j];
        if (pi == pj) same++;
        else if (pi.first == pj.first) vert++;
        else {
          double slope = (double)(pj.second - pi.second) / (pj.first - pi.first);
          map[slope]++;
          most = max(most, map[slope]);
        }
      }

      most = max(most, vert); // compare against special case
      most += same; // add dups
      res = max(res, most);
    }
    return res;
  }



  // Similar to longest ascending subsequence
  int largestSetOfPointsWithPositiveSlope(vector<pair<int, int>> points) {
    sort(points.begin(), points.end(), SlopeComparator());
    int res = 0;
    vector<int> M(points.size(), 0);
    for (int i = 0; i < points.size(); ++i) {
      for (int j = 0; j < i; ++j)
        if (points[j].second < points[i].second)
          M[i] = max(M[i], M[j]);
      
      M[i]++;
      res = max(res, M[i]);
    }

    return res == 1 ? 0 : res; // IMPORTANT, a single point cannot form a line!
  }



  // Integer to english words
  string digits[20] = { "Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten",
    "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen" };
  string tens[10] = { "Zero", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };
  int bil = 1000000000, mil = 1000000, tho = 1000, hun = 100;

  string integerToEnglishWords(int num) {
    if (num == 0) return "Zero";
    string res = int2str(num);
    res.erase(0, 1);
    return res;
  }

  string int2str(int n) {
    if (n >= bil)
      return int2str(n / bil) + " Billion" + int2str(n % bil);
    else if (n >= mil)
      return int2str(n / mil) + " Million" + int2str(n % mil);
    else if (n >= tho)
      return int2str(n / tho) + " Thousand" + int2str(n % tho);
    else if (n >= hun)
      return int2str(n / hun) + " Hundred" + int2str(n % hun);
    else if (n >= 20)
      return " " + tens[n / 10] + int2str(n % 10);
    else if (n >= 1)
      return " " + digits[n];
    else
      return ""; // don't forget this
  }



  // Equal length of ropes, lined up together. Each rope is cut into different segments.
  // Put a vertical line over those ropes, return the minimum number of segments that vertical line goes through
  // ie. if the line goes through the edges of two segmeents, it's not counted as "go through"
  int ropeCut(vector<vector<int>> ropes) {
    // build all edges
    int sum = 0;
    unordered_map<int, int> map;
    for (auto& r : ropes) {
      sum = 0;
      for (auto& s : r) {
        sum += s;
        map[sum]++;
      }
    }

    // edge case: if all ropes have 1 segment, we hav nowhere to place the vertical line (can't be at front, can't be at end)
    // we have to put it in the middle, which crosses all the ropes
    if (map.size() == 1)
      return ropes.size();

    // I want to go through the most edges
    int res = INT_MIN;
    for (int i = 1; i <= sum - 1; ++i) {
      res = max(res, map[i]);
    }
    // my answer: I align the vertical line with the most edges
    return ropes.size() - res;
  }




private:

  unsigned long long getHashCode(string small) {
    const int size = small.size();
    unsigned long long sum = 0;
    for (int i = 0; i < size; ++i) {
      auto t1 = (unsigned long long)(small[i] - 'a');
      auto t2 = long_pow(MAGIC_NUMBER, size - i - 1);
      auto t3 = t1 * t2;
      sum += t3;
    }
    return sum;
  }

  unsigned long long getHashCode(string large, int start, int end) {
    const int size = end - start + 1;
    unsigned long long sum = 0;
    for (int i = 0; i < size; ++i) {
      auto t1 = (unsigned long long)(large[i] - 'a');
      auto t2 = long_pow(MAGIC_NUMBER, size - i - 1);
      auto t3 = t1 * t2;
      sum += t3;
    }
    return sum;
  }

  void updateHashCode(string large, int start, int end, unsigned long long& currHash) {
    int size = end - start + 1;

    // 1. remove left most from polynomial equation
    currHash -= (large[start - 1] - 'a') * long_pow(MAGIC_NUMBER, size - 1);;
    // 2. all rest items * 26
    currHash *= 26;
    // 3. add new item into the equation
    currHash += large[end] - 'a';
  }

  unsigned long long long_pow(int a, int b) {
    unsigned long long res = 1;
    unsigned long long base = (unsigned long long)a;
    for (int i = 0; i < b; ++i) {
      res *= base;
    }
    return res;
  }
  

};
