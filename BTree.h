
#include <unordered_map>

#include "BTreeNode.h"
#include "BTreeIndexNode.h"

#pragma once

class BTree {

	std::unordered_map<int, BTreeNode*> m_pageCache;

	BTreeNode* m_pRoot;

public:
	BTree() {
		m_pRoot = NULL;
	}

	bool Insert( __int64 nNewKey ) { 
		if ( m_pRoot == NULL ) {
			m_pRoot = new BTreeIndexNode();
		}

		return m_pRoot->Insert( nNewKey );
	}

	bool HasKey( __int64 nNewKey ) {
		return m_pRoot->HasKey( nNewKey );
	}

	void print() {
		if ( m_pRoot == NULL ) {
			printf( "node is NULL" );
		} else {
			m_pRoot->print();
		}
	}
};