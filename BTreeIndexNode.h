#pragma once

class BTree;
#include "BTreeNode.h"


class BTreeIndexNode : public BTreeNode {
	friend class BTree;
	// key is 8 bytes
	// page number is 4 bytes
	// 8n + 4*(n+1) = 8192
	// 8n +4n +4 = 8192
	// 12n = 8188
	// n = 682 
	static const int m_nOrder = 682;
	__int64 m_key[m_nOrder];
	int m_pageNumbers[m_nOrder+1];
	int m_nKeys;
	static int m_nNextPageNumber;

public:
	BTreeIndexNode() {
		m_nKeys = 0;
		for ( int n = 0; n < m_nOrder; n++ ) {
			m_pageNumbers[n] = -1;
			m_key[n] = 0;
		}
		m_pageNumbers[m_nOrder] = -1;
		m_nPageNumber = m_nNextPageNumber++;
	}

	BTreeIndexNode( int nSinglePage ) {
		m_nKeys = 1;
		for ( int n = 0; n < m_nOrder; n++ ) {
			m_pageNumbers[n] = -1;
			m_key[n] = 0;
		}
		m_pageNumbers[m_nOrder] = -1;
		m_pageNumbers[0] = nSinglePage;
		m_nPageNumber = m_nNextPageNumber++;
	}

	void print() {
		printf( "[%d]%s ", m_nPageNumber, m_bIsLeaf ? "LEAF" : "INTERNAL" );
		printf( "%d:", m_nKeys );

		for ( int n = 0; n < m_nKeys; n++ ) {
			printf( " %lld[%d]", m_key[n], m_pageNumbers[n] );
		}
		printf( "\n" );
	}

	bool HasKey( __int64 nKey ) {
		// is this a leaf node?
		if ( m_bIsLeaf ) {
			return false;
		}

		int nIndex = 0;
		while ( nIndex < m_nKeys && nKey > m_key[nIndex] ) {
			nIndex += 1;
		}

		if ( nIndex < m_nKeys && nKey == m_key[nIndex] ) {
			return true;
		}

		// read m_pageNumber[nIndex];
		// search it recursively
		return false;
	}

	virtual bool IsFull() {
		return ( m_nKeys == m_nOrder - 1 );
	}

	bool Insert( __int64 nKey ) { 
		if ( m_nKeys == m_nOrder-1 ) {
			// it's full, splitting NYI
			return false;
		} else {
			// InsertNonFull( 
		}
		// figure out where the key goes
		// TODO: Binary Search
		int nInsertBefore = 0;
		while ( nInsertBefore < m_nKeys && m_key[nInsertBefore] < nKey ) {
			nInsertBefore += 1;
		}

		// move everyone else over
		for ( int nMove = m_nKeys-1; nMove >= nInsertBefore; nMove -- ) {
			m_key[nMove+1] = m_key[nMove];
		}
		m_key[nInsertBefore] = nKey;
		m_nKeys += 1;

		return true;
	}


	bool InsertNonFull( BTree* pTree,  __int64 nKey );
};

