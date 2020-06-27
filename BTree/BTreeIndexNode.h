#pragma once

template<int Tee> class BTree;
#include "BTreeNode.h"
#include "BTree.h"

template<int Tee>
class BTreeIndexNode : public BTreeNode {
	template<int Tee> friend class BTree;
	// key is 8 bytes
	// page number is 4 bytes
	// 8n + 4*(n+1) = 8192
	// 8n +4n +4 = 8192
	// 12n = 8188
	// n = 682 
	static const int m_tee = 2;
	__int64 m_key[2 * m_tee];
	int m_pageNumbers[2 * m_tee + 1];
	int m_nKeys;
	static int m_nNextPageNumber;
	BTree<Tee> * m_pOwner;

	void CommonInit() {
		m_nKeys = 0;
		for ( int n = 0; n < 2 * m_tee; n++ ) {
			m_pageNumbers[n] = -1;
			m_key[n] = 0;
		}
		m_pageNumbers[2 * m_tee] = -1;
		m_nPageNumber = m_nNextPageNumber++;
	}

public:
	BTreeIndexNode( BTree<Tee> *pOwner ) {
		CommonInit();
		m_pOwner = pOwner;
	}


	BTreeIndexNode( BTree<Tee> *pOwner, int nSinglePage ) {
		CommonInit();
		m_pOwner = pOwner;
		m_pageNumbers[0] = nSinglePage;
		m_nPageNumber = m_nNextPageNumber++;
	}

	void print();
	void printToString(std::string& str);

	bool HasKey( __int64 nKey ) {

		int nIndex = m_nKeys;
		while (nIndex > 0)
		{
			if (nKey == m_key[nIndex-1]) {
				return true;
			}
			if (nKey < m_key[nIndex-1]) {
				nIndex--;
			}
			else {
				break;
			}

		}

		if (nIndex == -1 || m_pageNumbers[nIndex] == -1) {
			return false;
		}

		BTreeIndexNode* pChild = m_pOwner->GetPage(m_pageNumbers[nIndex]);
		return pChild->HasKey(nKey);
	}

	virtual bool IsFull() {
		// return ( m_nKeys == 2 * m_tee - 1 );
		return (m_nKeys == 2 * m_tee);
	}

	bool InsertNonFull( __int64 nKey );
};

template<int Tee>
int BTreeIndexNode<Tee>::m_nNextPageNumber = 0;

template<int Tee>
void BTreeIndexNode<Tee>::printToString(std::string& str) {

	char sz[100];
	sprintf(sz, "[%d]%s ", m_nPageNumber, m_bIsLeaf ? "LEAF" : "INTERNAL");
	str.append(sz);

	sprintf(sz, "%d/%d:", m_nKeys, 2 * m_tee);
	str.append(sz);

	sprintf(sz, "[%d]", m_pageNumbers[0]);
	str.append(sz);
	for (int n = 0; n < m_nKeys; n++) {
		sprintf(sz, " %lld [%d]", m_key[n], m_pageNumbers[n + 1]);
		str.append(sz);
	}
	str.append("\n");

	for (int n = 0; n < m_nKeys + 1; n++) {
		if (m_pageNumbers[n] != -1) {
			BTreeIndexNode* pNode = m_pOwner->GetPage(m_pageNumbers[n]);
			pNode->printToString(str);
		}
	}
}

template<int Tee>
void BTreeIndexNode<Tee>::print( ) {
	printf( "[%d]%s ", m_nPageNumber, m_bIsLeaf ? "LEAF" : "INTERNAL" );
	printf( "%d/%d:", m_nKeys, 2 * m_tee );

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

template<int Tee>
bool BTreeIndexNode<Tee>::InsertNonFull( __int64 nKey ) { 
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

