#include "TestFixture.h"
#include <OOD/LRUCacheInt.h>
#include <OOD/LRUCache.h>
#include <OOD/TicTacToe.h>
#include <OOD/AllOne.h>
#include <OOD/FirstNonRepeating.h>

namespace OODTests {

	TEST(OODTests, LRUCacheInt) {
		int val = 0;
		bool res = false;

		LRUCacheInt obj(2);

		obj.set(1, 1);   // [1]
		obj.set(2, 2);   // [2 1]
		EXPECT_TRUE(obj.get(1, val)); // [1 2]
		EXPECT_EQ(val, 1);

		obj.set(3, 3);   // [3 1], 2 pushed out
		EXPECT_FALSE(obj.get(2, val));

		obj.set(4, 4);   // [4 3], 1 pushed out
		EXPECT_FALSE(obj.get(1, val));
		EXPECT_TRUE(obj.get(3, val)); // [3 4]
		EXPECT_EQ(val, 3);
		EXPECT_TRUE(obj.get(4, val)); // [4 3]
		EXPECT_EQ(val, 4);
	}

	TEST(OODTests, LRUCache) {
		int val = 0;
		bool res = false;

		LRUCache<int, int> obj(2);

		obj.set(1, 1);   // [1]
		obj.set(2, 2);   // [2 1]
		EXPECT_TRUE(obj.get(1, val)); // [1 2]
		EXPECT_EQ(val, 1);

		obj.set(3, 3);   // [3 1], 2 pushed out
		EXPECT_FALSE(obj.get(2, val));

		obj.set(4, 4);   // [4 3], 1 pushed out
		EXPECT_FALSE(obj.get(1, val));
		EXPECT_TRUE(obj.get(3, val)); // [3 4]
		EXPECT_EQ(val, 3);
		EXPECT_TRUE(obj.get(4, val)); // [4 3]
		EXPECT_EQ(val, 4);
	}

	TEST(OODTests, TicTacToe) {
		TicTacToe ttt(3);
		// invalid - out of bound / invalid player
		EXPECT_EQ(-1, ttt.move(0, -1, 1));
		EXPECT_EQ(-1, ttt.move(-1, 1, 1));
		EXPECT_EQ(-1, ttt.move(0, 3, 1));
		EXPECT_EQ(-1, ttt.move(0, 0, 3));

		// valid moves
		EXPECT_EQ(0, ttt.move(0, 0, 1));
		EXPECT_EQ(0, ttt.move(0, 1, 2));
		EXPECT_EQ(0, ttt.move(1, 1, 1));
		EXPECT_EQ(0, ttt.move(2, 2, 2));
		EXPECT_EQ(0, ttt.move(1, 0, 1));
		EXPECT_EQ(0, ttt.move(2, 0, 2));
		EXPECT_EQ(0, ttt.move(2, 1, 1));
		EXPECT_EQ(0, ttt.move(0, 2, 2));

		// invalid - visited
		EXPECT_EQ(-1, ttt.move(0, 0, 1));

		// winner
		EXPECT_EQ(1, ttt.move(1, 2, 1));
	}

	TEST(OODTests, AllOne) {
		AllOne obj;

		obj.inc("apple");
		obj.inc("grape");
		obj.inc("apple");
		EXPECT_EQ(obj.getMaxKey(), "apple");
		EXPECT_EQ(obj.getMinKey(), "grape");

		obj.dec("non-existing");
		obj.dec("grape");
		EXPECT_EQ(obj.getMaxKey(), "apple");
		EXPECT_EQ(obj.getMinKey(), "apple"); // "grape" is now gone
	}

	TEST(OODTests, FirstNonRepeating) {
		FirstNonRepeating obj;
		obj.read('a');
		EXPECT_EQ(obj.firstNonRepeating(), 'a');

		obj.read('b');
		EXPECT_EQ(obj.firstNonRepeating(), 'a');

		obj.read('c');
		EXPECT_EQ(obj.firstNonRepeating(), 'a');

		obj.read('a');
		EXPECT_EQ(obj.firstNonRepeating(), 'b');

		obj.read('c');
		EXPECT_EQ(obj.firstNonRepeating(), 'b');

		obj.read('c');
		EXPECT_EQ(obj.firstNonRepeating(), 'b');

		obj.read('b');
		EXPECT_EQ(obj.firstNonRepeating(), ' ');
	}
}