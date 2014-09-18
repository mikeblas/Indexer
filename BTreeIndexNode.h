#pragma once

class BTree;
#include "BTreeNode.h"
#include "BTree.h"


class BTreeIndexNode : public BTreeNode {
	friend class BTree;
	// key is 8 bytes
	// page number is 4 bytes
	// 8n + 4*(n+1) = 8192
	// 8n +4n +4 = 8192
	// 12n = 8188
	// n = 682 
	// static const int m_nOrder = 682;
	static const int m_nOrder = 2;
	__int64 m_key[m_nOrder];
	int m_pageNumbers[m_nOrder+1];
	int m_nKeys;
	static int m_nNextPageNumber;
	BTree* m_pOwner;

public:
	BTreeIndexNode( BTree *pOwner ) {
		m_pOwner = pOwner;
		m_nKeys = 0;
		for ( int n = 0; n < m_nOrder; n++ ) {
			m_pageNumbers[n] = -1;
			m_key[n] = 0;
		}
		m_pageNumbers[m_nOrder] = -1;
		m_nPageNumber = m_nNextPageNumber++;
	}

	BTreeIndexNode( BTree *pOwner, int nSinglePage ) {
		m_pOwner = pOwner;
		m_nKeys = 0;
		for ( int n = 0; n < m_nOrder; n++ ) {
			m_pageNumbers[n] = -1;
			m_key[n] = 0;
		}
		m_pageNumbers[m_nOrder] = -1;
		m_pageNumbers[0] = nSinglePage;
		m_nPageNumber = m_nNextPageNumber++;
	}

	void print( );

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
		return ( m_nKeys == m_nOrder );
	}

	bool InsertNonFull( __int64 nKey );


	bool InsertNonFull( BTree* pTree,  __int64 nKey );
};

