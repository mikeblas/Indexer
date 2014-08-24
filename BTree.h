
#include <unordered_map>

#include "BTreeNode.h"

#pragma once

class BTree {

	std::unordered_map<int, BTreeNode*> m_pageCache;

	BTreeNode* m_pRoot;

public:
	BTree() {
		m_pRoot = NULL;
	}

	void Insert( __int64 nNewKey ) { 
	}

	bool HasKey( __int64 nNewKey ) {
		return m_pRoot->HasKey( nNewKey );
	}
};