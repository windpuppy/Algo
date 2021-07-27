#include "TestFixture.h"
#include <DFS/DFS.h>

namespace DFSTests {
	DFS obj;

	TEST(DFSTests, Subsets) {
		auto res = obj.subsets("");
		EXPECT_EQV(res, vector<string>{""});

		vector<string> expected{ "abc", "ab", "ac", "a", "bc", "b", "c", "" };
		res = obj.subsets("abc");
		EXPECT_EQV(res, expected);

		expected = vector<string>{ "", "a", "b", "c", "ab", "ac", "bc", "abc" };
		res = obj.subsets_bfs("abc");
		EXPECT_EQV(res, expected);

		expected = vector<string>{ "", "a", "b", "ab", "c", "ac", "bc", "abc" };
		res = obj.subsets_bfs2("abc");
		EXPECT_EQV(res, expected);

		expected = vector<string>{ "", "a", "b", "ab", "c", "ac", "bc", "abc" };
		res = obj.subsets_bitwise("abc");
		EXPECT_EQV(res, expected);
	}

	TEST(DFSTests, ValidParentheses) {
		auto res = obj.validParentheses(2);
		vector<string> expected{ "(())", "()()" };
		EXPECT_EQV(res, expected);

		res = obj.validParentheses(3);
		expected = vector<string>{ "((()))", "(()())", "(())()", "()(())", "()()()" };
		EXPECT_EQV(res, expected);
	}

	TEST(DFSTests, CoinCombinations) {
		vector<int> coins{ 25, 10, 5, 1 };
		auto res = obj.coinCombinations(coins, 99);
		EXPECT_EQ(res.size(), 213);

		coins = vector<int>{ 1, 5, 10, 25 };
		res = obj.coinCombinations(coins, 99);
		EXPECT_EQ(res.size(), 213);

		coins = vector<int>{ 34, 31, 29, 16, 2 };
		res = obj.coinCombinations(coins, 20);
		vector<vector<int>> expected{ vector<int>{0, 0, 0, 0, 10}, vector<int>{0, 0, 0, 1, 2} };
		EXPECT_EQV(res[0], expected[0]);
		EXPECT_EQV(res[1], expected[1]);
	}

	TEST(DFSTests, Permutations) {
		auto res = obj.permutations("abc");
		vector<string> expected{ "abc", "acb", "bac", "bca", "cba", "cab" };
		EXPECT_EQV(res, expected);
	}
};
