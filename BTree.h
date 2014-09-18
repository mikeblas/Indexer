
#pragma once

#include <unordered_map>

#include "BTreeNode.h"
#include "BTreeIndexNode.h"

class BTree {
public:
	BTreeIndexNode* m_pRoot;
	std::unordered_map<int, BTreeIndexNode*> m_pageCache;

public:
	BTree() {
		m_pRoot = NULL;
	}

	bool Insert( __int64 nNewKey ) { 
		if ( m_pRoot == NULL ) {
			m_pRoot = new BTreeIndexNode( this );
			m_pageCache.emplace( m_pRoot->GetPageNumber(), m_pRoot );
			return m_pRoot->InsertNonFull( nNewKey );
		}

		if ( m_pRoot->IsFull() ) {
			BTreeIndexNode* oldRoot = (BTreeIndexNode*) m_pRoot;
			m_pRoot = new BTreeIndexNode( this, oldRoot->GetPageNumber() );
			m_pageCache.emplace( m_pRoot->GetPageNumber(), m_pRoot );
			m_pRoot->SetLeaf( false );
			// m_pRoot->m_pageNumbers[0] = oldRoot->m_nPageNumber;
			SplitChild( (BTreeIndexNode*) m_pRoot, 0, oldRoot );
			return m_pRoot->InsertNonFull( nNewKey );
		} else {
			return m_pRoot->InsertNonFull( nNewKey );
		}
	}

	void SplitChild( BTreeIndexNode* pParent, int nIndex, BTreeIndexNode* pNode ) {
		BTreeIndexNode* pNewNode = new BTreeIndexNode(this);
		m_pageCache.emplace( pNewNode->GetPageNumber(), pNewNode );

		pNewNode->SetLeaf( pNode->IsLeaf() );

		pNewNode->m_nKeys = pNode->m_nKeys /2;

		// right half of node into new node
		for ( int n = 0; n < pNode->m_nKeys/2; n++ ) {
			pNewNode->m_key[n] = pNode->m_key[n + pNode->m_nKeys/2 ];
		}

		// copy page numbers if not a leaf
		if ( ! pNode->IsLeaf() ) {
			for ( int n = 0; n < pNode->m_nKeys/2; n++ ) {
				pNewNode->m_pageNumbers[n] = pNode->m_pageNumbers[n + pNode->m_nKeys/2];
			}
		}

		// node is now half as big as it was
		pNode->m_nKeys = pNode->m_nKeys/2;

		// move everything in parent to the right in order to insert new one
		for ( int n = pParent->m_nKeys; n >= nIndex+1; n-- ) {
			pParent->m_pageNumbers[n+1] = pParent->m_pageNumbers[n];
		}
		pParent->m_pageNumbers[nIndex+1] = pNewNode->GetPageNumber();

		for ( int n = pParent->m_nKeys-1; n >= nIndex; n-- ) {
			pParent->m_key[n+1] = pParent->m_key[n];
		}

		pParent->m_key[nIndex] = pNode->m_key[ pNode->m_nOrder - 1];

		// pParent->m_key[nIndex] = pNode->m_key[ pNode->m_nKeys - 1];
		// pParent->m_key[nIndex] = pNode->m_key[ ( pNode->m_nKeys / 2 )];
		// pParent->m_key[nIndex] = -9999;
		pParent->m_pageNumbers[nIndex] = pNode->GetPageNumber();
		pParent->m_nKeys++;
	}

	bool HasKey( __int64 nNewKey ) {
		return m_pRoot->HasKey( nNewKey );
	}

	void print() {
		if ( m_pRoot == NULL ) {
			printf( "node is NULL" );
		} else {
			m_pRoot->print( );
		}
		printf( "\n" );
	}

	BTreeIndexNode* GetPage( int nPageNumber ) {
		return m_pageCache[nPageNumber];
	}

};

