#include "String.h"
#include "HashMap.h"

int main()
{
	String sol;

	// Top K frequent words
	{
		vector<string> input{ "d","a","c","b","d","a","b","b","a","d","d","a","d" };
		auto res = sol.topKFrequentWords(input, 5);
	}

	// Missing number
	{
		vector<int> input{ 12, 11, 10, 9, 4, 5, 6, 7, 2, 3, 8 };
		auto res = sol.missingNumber(input);
	}

	// Common numbers
	{
		vector<int> a{ 1, 1, 2, 3, 3 };
		vector<int> b{ 2, 3, 3, 4, 5 };
		auto res = sol.commonNumbers(a, b);
	}

	// Remove certain characters
	{
		auto res = sol.removeCertainCharacters("abcde", "cef");
	}

	// Remove spaces
	{
		auto res = sol.removeSpaces("  i love laicode  ");
	}

	// Remove adjacent repeated chars 1 - 4
	{
		auto res = sol.removeAdjacentRepeatedChars("aaabbbc"); // abc
		res = sol.removeAdjacentRepeatedChars2("aaabbbc"); // aabbc
		res = sol.removeAdjacentRepeatedChars3("aaabbbc"); // c
		res = sol.removeAdjacentRepeatedChars4("abbbbacd"); // cd
		res = sol.removeAdjacentRepeatedChars4("aaaaa"); // ""
	}

	// Is substring
	{
		auto res = sol.isSubstring("abcde", "bcd");
		res = sol.isSubstring_RabinKarp("abcde", "bcd");
	}

	// Reverse string
	{
		auto res = sol.reverseString("abc");
	}

	// Reverse words
	{
		auto res = sol.reverseWords("Hi there");
	}

	// Right shift
	{
		auto res = sol.rightShift("abcdefg", 3);
	}

	// String replace
	{
		auto res = sol.replace("appledog", "apple", "dog");
		res = sol.replace("dogapple", "dog", "apple");
		res = sol.replace("applecatapp", "app", "pear");
	}

	// ReOrder array 2
	{
		vector<int> input{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
		auto res = sol.reorderArray(input);
	}

	// Compress string 2
	{
		auto res = sol.compress2("aaabbcdee");
	}

	// Dceompress string 1
	{
		auto res = sol.decompress("ap2lec3n");
	}

	// Decompress string 2
	{
		auto res = sol.decompress2("a2b0c1d3"); // 0 will be ignored
	}

	// Encode Space
	{
		auto res = sol.encodeSpace("ab d");
	}

	// Longest no repeat
	{
		auto res = sol.longestSubstringNoDuplicates("bcdfbd");
		res = sol.longestSubstringNoDuplicates("abcdecf");
		res = sol.longestSubstringNoDuplicates2("abcdecf");
	}

	// All anagrams
	{
		auto res = sol.allAnagrams("abcbaczzzab", "ab");
		res = sol.allAnagrams("abcbacaaaaaab", "ab");
	}

	// Mininum window substring
	{
		auto res = sol.minimumWindowSubstring("ADOBECODEBANC", "ABC"); // BANC
	}

	// Count and say
	{
		auto res = sol.countAndSay(11);
	}

	// Intersect
	{
		vector<int> a{ 1, 1, 2, 2 };
		vector<int> b{ 1, 2, 2, 3 };
		auto res = sol.intersectOfTwoArrays(a, b); // 1, 2, 2
	}

	// Valid palindrome - alphanumeric
	{
		string input("ab$c b.;A . ");
		auto res = sol.validPalindromeAlphaNumeric(input);
		string input2("0P");
		res = sol.validPalindromeAlphaNumeric(input2);
	}

	// Valid palindrome - can delete 1 char
	{
		string input("aba");
		auto res = sol.validPalinedromeWithOneDelete(input);
		input = "deeee";
		res = sol.validPalinedromeWithOneDelete(input);
		input = "ebcbbececabbacecbbcbe";
		res = sol.validPalinedromeWithOneDelete(input);
	}

	// Longest palindromic substring
	{
		auto res = sol.longestPalindromeSubstring("abbc"); // bb
		res = sol.longestPalindromeSubstring("geeks"); // ee
		res = sol.longestPalindromeSubstring("abcbcbd"); // bcbcb
		res = sol.longestPalindromeSubstring("babaddtattarrattatddetartrateedredividerb");
	}

	// Longest palindrome subsequence
	{
		auto res = sol.longestPalindromeSubsequence("abca"); // 3
	}

	// Count palindrome substrings - can repeat, e.g. "aaa" - a, a, a, aa, aa, aaa
	{
		auto res = sol.countPalindromeSubstrings("abc"); // 3: a, b, c
		res = sol.countPalindromeSubstrings("aaa"); // 6: a, a, a, aa, aa, aaa
	}

	// Least insertions to form a palindrome
	{
		auto res = sol.leastInsertionsToFormPalindrome("abcd"); // 3
		res = sol.leastInsertionsToFormPalindrome("ilovegoogle");
	}

	// Palindrome permutation
	{
		auto res = sol.palindromePermutation("carerac"); // true
	}

	// Valid parenthese
	{
		auto res = sol.validParenthese("[{()}()]");
		res = sol.validParenthese("(]");
	}

	// Largest set of points with positive slope
	{
		vector<pair<int, int>> points{ {0,0},{1,1},{2,3},{3,2},{3,3} };
		auto res = sol.largestSetOfPointsWithPositiveSlope(points);
	}

	// Rope Cut
	{
		vector<vector<int>> ropes{ {1,2,2,1},{3,1,2},{1,3,2},{2,4},{3,1,2},{1,3,1,1} };
		auto res = sol.ropeCut(ropes);
	}

	cin.get();
	return 0;
}
