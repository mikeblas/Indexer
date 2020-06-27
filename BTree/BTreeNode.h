
#pragma once

template<int Tee> class BTree;

class BTreeNode {

protected:
	bool m_bIsLeaf;
	int m_nPageNumber;
	BTreeNode() {
		m_bIsLeaf = true;
	}

public:
	void SetLeaf( bool bLeaf ) { 
		m_bIsLeaf = bLeaf;
	}

	int GetPageNumber() {
		return m_nPageNumber;
	}

	virtual bool IsFull() = 0;

	virtual ~BTreeNode() {
	}

	virtual bool HasKey( __int64 nKey ) = 0;

	virtual bool IsLeaf() {
		return m_bIsLeaf;
	}

	virtual bool InsertNonFull( __int64 nKey ) = 0;

	virtual void print( ) = 0;
};
