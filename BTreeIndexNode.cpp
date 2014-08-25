
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
