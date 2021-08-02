#include "String.h"
#include "HashMap.h"

int main()
{
	String obj;

	// Reverse string
	{
		auto res = obj.reverseString("abc");
	}

	// Reverse words
	{
		auto res = obj.reverseWords("Hi there");
	}

	// String replace
	{
		auto res = obj.replace("appledog", "apple", "dog");
		res = obj.replace("dogapple", "dog", "apple");
		res = obj.replace("applecatapp", "app", "pear");
	}

	// Encode Space
	{
		auto res = obj.encodeSpace("ab d");
	}

	// Compress string 2
	{
		auto res = obj.compress2("aaabbcdee");
	}

	// Dceompress string 1
	{
		auto res = obj.decompress("ap2lec3n");
	}

	// Decompress string 2
	{
		auto res = obj.decompress2("a2b0c1d3"); // 0 will be ignored
	}

	// ReOrder array 2
	{
		vector<int> input{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
		auto res = obj.reorderArray(input);
	}

	

	// Longest no repeat
	{
		auto res = obj.longestSubstringNoDuplicates("bcdfbd");
		res = obj.longestSubstringNoDuplicates("abcdecf");
		res = obj.longestSubstringNoDuplicates2("abcdecf");
	}

	// All anagrams
	{
		auto res = obj.allAnagrams("abcbaczzzab", "ab");
		res = obj.allAnagrams("abcbacaaaaaab", "ab");
	}

	// Mininum window substring
	{
		auto res = obj.minimumWindowSubstring("ADOBECODEBANC", "ABC"); // BANC
	}

	// Count and say
	{
		auto res = obj.countAndSay(11);
	}

	// Intersect
	{
		vector<int> a{ 1, 1, 2, 2 };
		vector<int> b{ 1, 2, 2, 3 };
		auto res = obj.intersectOfTwoArrays(a, b); // 1, 2, 2
	}

	// Valid palindrome - alphanumeric
	{
		string input("ab$c b.;A . ");
		auto res = obj.validPalindromeAlphaNumeric(input);
		string input2("0P");
		res = obj.validPalindromeAlphaNumeric(input2);
	}

	// Valid palindrome - can delete 1 char
	{
		string input("aba");
		auto res = obj.validPalinedromeWithOneDelete(input);
		input = "deeee";
		res = obj.validPalinedromeWithOneDelete(input);
		input = "ebcbbececabbacecbbcbe";
		res = obj.validPalinedromeWithOneDelete(input);
	}

	// Longest palindromic substring
	{
		auto res = obj.longestPalindromeSubstring("abbc"); // bb
		res = obj.longestPalindromeSubstring("geeks"); // ee
		res = obj.longestPalindromeSubstring("abcbcbd"); // bcbcb
		res = obj.longestPalindromeSubstring("babaddtattarrattatddetartrateedredividerb");
	}

	// Longest palindrome subsequence
	{
		auto res = obj.longestPalindromeSubsequence("abca"); // 3
	}

	// Count palindrome substrings - can repeat, e.g. "aaa" - a, a, a, aa, aa, aaa
	{
		auto res = obj.countPalindromeSubstrings("abc"); // 3: a, b, c
		res = obj.countPalindromeSubstrings("aaa"); // 6: a, a, a, aa, aa, aaa
	}

	// Least insertions to form a palindrome
	{
		auto res = obj.leastInsertionsToFormPalindrome("abcd"); // 3
		res = obj.leastInsertionsToFormPalindrome("ilovegoogle");
	}

	// Palindrome permutation
	{
		auto res = obj.palindromePermutation("carerac"); // true
	}

	// Valid parenthese
	{
		auto res = obj.validParenthese("[{()}()]");
		res = obj.validParenthese("(]");
	}

	// Largest set of points with positive slope
	{
		vector<pair<int, int>> points{ {0,0},{1,1},{2,3},{3,2},{3,3} };
		auto res = obj.largestSetOfPointsWithPositiveSlope(points);
	}

	// Rope Cut
	{
		vector<vector<int>> ropes{ {1,2,2,1},{3,1,2},{1,3,2},{2,4},{3,1,2},{1,3,1,1} };
		auto res = obj.ropeCut(ropes);
	}

	cin.get();
	return 0;
}
