// Indexer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PagedFile.h"
#include "BTree.h"
#include "BTreeIndexNode.h"



void TreeTest1()
{
	BTree<2> tree;

	tree.Insert(4);
	tree.print();
	tree.Insert(0);
	tree.print();
	tree.Insert(6);
	tree.print();
	tree.Insert(8);
	tree.print();
	tree.Insert(2);
	tree.print();
	tree.Insert(1);
	tree.print();
	tree.Insert(7);
	tree.print();
	tree.Insert(3);
	tree.print();
	tree.Insert(9);
	tree.print();
	tree.Insert(5);
	tree.print();
	printf( "\n" );
}

void TreeTest2()
{
	BTree<2> tree;

	tree.Insert(5);
	tree.Insert(9);
	tree.print();
	printf( "\n" );
	tree.Insert(3);
	tree.print();
	printf( "\n" );
	tree.Insert(7);
	tree.print();
	printf( "\n" );
	tree.Insert(1);
	tree.print();
	printf( "\n" );
	tree.Insert(2);
	tree.Insert(8);
	tree.Insert(6);
	tree.Insert(0);
	tree.Insert(4);
	tree.print();
	printf( "\n" );
}

int _tmain(int argc, _TCHAR* argv[])
{
	CPagedFile pf( "test.db", 8192, 10000 );
	byte b[8192];
	b[0] = 33;
	b[1] = 34;
	b[2] = 35;
	b[3] = 36;
	pf.WritePage( 3153, b );
	pf.Close();

	CPagedFile pf2( "test.db", 8192 );
	byte b2[8192];
	bool r = pf2.ReadPage( 3153, b2 );
	printf("%d\n", r); 
	printf("%d %d %d %d\n", b2[0], b2[1], b2[2], b2[3] );
	pf2.Close();


	printf("=== test1\n\n");
	TreeTest1();

	printf("=== test2\n\n");
	TreeTest2();

	BTree<2> tree;
	/*
	// two, from database book
	tree.Insert(8);
	tree.Insert(5);
	tree.print();
	printf( "---\n" );

	tree.Insert(1);
	tree.print();
	printf( "---\n" );

	tree.Insert(7);
	tree.print();
	printf( "---\n" );

	tree.Insert(3);
	tree.print();
	printf( "---\n" );
	tree.Insert(12);
	tree.Insert(9);
	tree.Insert(6);
	tree.print();
	printf( "\n" );
	*/

	/*
	for ( int n = 0; n < 1500; n += 2 ) {
		if ( ! tree.Insert( n ) ) {
			printf( "%d\n", n );
			break;
		}
	}
	*/

	/*
	tree.print();
	printf( "\n" );
	
	tree.m_pageCache.at(0)->print( );
	printf( "\n" );

	tree.m_pageCache.at(2)->print(  );
	printf( "\n" );
	*/

	
	return 0;
}

