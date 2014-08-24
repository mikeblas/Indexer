// Indexer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PagedFile.h"



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

	return 0;
}

