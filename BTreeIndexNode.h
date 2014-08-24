
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
	bool m_bIsLeaf;
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
		m_bIsLeaf = true;
		m_pageNumber[m_nOrder] = -1;
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
};