
#include "BTreeNode.h"

#pragma once

class BTreeIndexNode : public BTreeNode {
	// key is 8 bytes
	// page number is 4 bytes
	// 8n + 4*(n+1) = 8192
	// 8n +4n +4 = 8192
	// 12n = 8188
	// n = 682 
	static const int m_nOrder = 682;
	__int64 m_key[m_nOrder];
	int m_pageNumber[m_nOrder+1];
	int m_nKeys;

public:
	BTreeIndexNode() {
		m_nKeys = 0;
		for ( int n = 0; n < m_nOrder; n++ ) {
			m_pageNumber[n] = -1;
			m_key[n] = 0;
		}
		m_pageNumber[m_nOrder] = -1;
	}

	void print() {
		printf( "%s ", m_bIsLeaf ? "LEAF" : "INTERNAL" );
		printf( "%d:", m_nKeys );

		for ( int n = 0; n < m_nKeys; n++ ) {
			printf( " %lld", m_key[n] );
		}
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

	bool Insert( __int64 nKey ) { 
		if ( m_nKeys == m_nOrder-1 ) {
			// it's full, splitting NYI
			return false;
		}

		// figure out where the key goes
		// TODO: Binary Search
		int nInsertAt = 0;
		while ( nInsertAt < m_nKeys && m_key[nInsertAt] < nKey ) {
			nInsertAt += 1;
		}

		// move everyone else over
		for ( int nMove = m_nKeys-1; nMove >= nInsertAt; nMove -- ) {
			m_key[nMove+1] = m_key[nMove];
		}
		m_key[nInsertAt] = nKey;
		m_nKeys += 1;

		return true;
	}
};