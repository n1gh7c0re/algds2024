#include "pch.h"
#include "..\Algorithm\main.h"

// tests for AddNode function
TEST(Test, t1) {
	Treap Treap;
	Treap.root = NULL;
	char arr[100] = "\0";
	
	AddNode(&Treap, 7, 10);
	AddNode(&Treap, 21, 5);
	AddNode(&Treap, 35, 20);

	ResultInOrder(Treap.root, arr);
	ASSERT_STREQ("(35, 20) (7, 10) (21, 5) ", arr);
}

TEST(Test, t2) {
	Treap Treap;
	Treap.root = NULL;
	char arr[100] = "\0";

	AddNode(&Treap, 7, 10);
	AddNode(&Treap, 21, 15);
	AddNode(&Treap, 35, 10);

	ResultInOrder(Treap.root, arr);
	ASSERT_STREQ("(21, 15) (7, 10) (35, 10) ", arr);
}

// tests for DeleteNode function
TEST(Test, t3) {
	Treap Treap;
	Treap.root = NULL;
	char arr[100] = "\0";

	AddNode(&Treap, 7, 10);
	AddNode(&Treap, 21, 15);
	AddNode(&Treap, 35, 20);
	DeleteNode(&Treap, 7);

	ResultInOrder(Treap.root, arr);
	ASSERT_STREQ("(35, 20) (21, 15) ", arr);
}

TEST(Test, t4) {
	Treap Treap;
	Treap.root = NULL;
	char arr[100] = "\0";

	AddNode(&Treap, 7, 10);
	AddNode(&Treap, 21, 15);
	AddNode(&Treap, 35, 10);
	DeleteNode(&Treap, 7);

	ResultInOrder(Treap.root, arr);
	ASSERT_STREQ("(21, 15) (35, 10) ", arr);
}