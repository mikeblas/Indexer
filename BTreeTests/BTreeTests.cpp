#include "pch.h"
#include "CppUnitTest.h"


#include "PagedFile.h"
#include "BTree.h"
#include "BTreeIndexNode.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BTreeTests
{
	TEST_CLASS(BTreeTests)
	{
	public:
		
		// inserts 10 items, tests they're found
		// also checks that non-existent keys are not found, too
		TEST_METHOD(InsertionTest1)
		{
			BTree<2> tree;

			tree.Insert(4);
			tree.Insert(0);
			tree.Insert(6);
			tree.Insert(8);
			tree.Insert(2);
			tree.Insert(1);
			tree.Insert(7);
			tree.Insert(3);
			tree.Insert(9);
			tree.Insert(5);

			std::string str;
			tree.printToString(str);
			Logger::WriteMessage(str.c_str());

			Assert::IsTrue(tree.HasKey(0));
			Assert::IsTrue(tree.HasKey(1));
			Assert::IsTrue(tree.HasKey(2));
			Assert::IsTrue(tree.HasKey(3));
			Assert::IsTrue(tree.HasKey(4));
			Assert::IsTrue(tree.HasKey(5));
			Assert::IsTrue(tree.HasKey(6));
			Assert::IsTrue(tree.HasKey(7));
			Assert::IsTrue(tree.HasKey(8));
			Assert::IsTrue(tree.HasKey(9));

			Assert::IsFalse(tree.HasKey(135));
			Assert::IsFalse(tree.HasKey(-33));
		}

		// inserts 10 items, tests they're found
		// also checks that non-existent keys are not found, too
		TEST_METHOD(InsertionTest2)
		{
			BTree<2> tree;

			tree.Insert(5);
			tree.Insert(9);
			tree.Insert(3);
			tree.Insert(7);
			tree.Insert(1);
			tree.Insert(2);
			tree.Insert(8);
			tree.Insert(6);
			tree.Insert(0);
			tree.Insert(4);

			Assert::IsTrue(tree.HasKey(0));
			Assert::IsTrue(tree.HasKey(1));
			Assert::IsTrue(tree.HasKey(2));
			Assert::IsTrue(tree.HasKey(3));
			Assert::IsTrue(tree.HasKey(4));
			Assert::IsTrue(tree.HasKey(5));
			Assert::IsTrue(tree.HasKey(6));
			Assert::IsTrue(tree.HasKey(7));
			Assert::IsTrue(tree.HasKey(8));
			Assert::IsTrue(tree.HasKey(9));

			Assert::IsFalse(tree.HasKey(135));
			Assert::IsFalse(tree.HasKey(-33));
		}


		// an empty tree should have nothing
		TEST_METHOD(EmptyTest1)
		{
			BTree<2> tree;
			Assert::IsFalse(tree.HasKey(532));
		}
	};
}
