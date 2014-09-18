
#include "stdafx.h"
#include "BTree.h"
#include "BTreeIndexNode.h"

int BTreeIndexNode::m_nNextPageNumber = 0;


bool BTreeIndexNode::InsertNonFull( BTree* pTree,  __int64 nKey ) {
	if ( this->IsLeaf() ) {
		int nIndex = m_nKeys;
		while ( nIndex >= 1 && nKey < m_key[nIndex] ) {
			m_key[nIndex+1] = m_key[nIndex];
			nIndex--;
		}

		m_key[nIndex+1] = nKey;
		m_nKeys += 1;
	} else {
		int nIndex = m_nKeys;
		while ( nIndex >= 1 && nKey < m_key[nIndex] ) {
			nIndex--;
		}

		nIndex++;

		BTreeIndexNode* pNode = pTree->m_pageCache.at( m_pageNumbers[nIndex] );
		if ( pNode->m_nKeys == m_nOrder - 1 ) {
		}

	}

	return true;
}

void BTreeIndexNode::print( ) {
	printf( "[%d]%s ", m_nPageNumber, m_bIsLeaf ? "LEAF" : "INTERNAL" );
	printf( "%d:", m_nKeys );

	printf( "[%d]", m_pageNumbers[0] );
	for ( int n = 0; n < m_nKeys; n++ ) {
		printf( " %lld [%d]", m_key[n], m_pageNumbers[n+1] );
	}
	printf( "\n" );

	for ( int n = 0; n < m_nKeys+1; n++ ) {
		if ( m_pageNumbers[n] != -1 ) {
			BTreeIndexNode *pNode = m_pOwner->GetPage( m_pageNumbers[n] );
			pNode->print( );
		}
	}
}

bool BTreeIndexNode::InsertNonFull( __int64 nKey ) { 
	if ( IsLeaf() ) {
		// TODO: Binary Search
		int nInsertBefore = m_nKeys;
		while ( nInsertBefore > 0 && nKey < m_key[nInsertBefore-1] ) {
			m_key[nInsertBefore] = m_key[nInsertBefore-1];
			nInsertBefore --;
		}
		m_key[nInsertBefore] = nKey;
		m_nKeys += 1;
	} else {
		// not a leaf; recurse down to find out where we belong
		int nInsertBefore = m_nKeys;
		while ( nInsertBefore > 0 && nKey < m_key[nInsertBefore-1] ) {
			nInsertBefore --;
		}

		// DiskRead(page[nInsertBefore]);
		BTreeIndexNode *pChild = m_pOwner->GetPage( m_pageNumbers[nInsertBefore] );
		if ( pChild->IsFull() ) {
			m_pOwner->SplitChild( this, nInsertBefore, pChild );
			if ( nKey > m_key[nInsertBefore] ) {
				nInsertBefore++;
				pChild = m_pOwner->GetPage( m_pageNumbers[nInsertBefore] );
			}
		}

		pChild->InsertNonFull(nKey);
	}

	return true;
}