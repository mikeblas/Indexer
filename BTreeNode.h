

#pragma once

class BTreeNode {


protected:
	bool m_bIsLeaf;
	BTreeNode() {
		m_bIsLeaf = true;
	}

public:

	virtual ~BTreeNode() {
	}

	virtual bool HasKey( __int64 nKey ) = 0;

	virtual bool IsLeaf() {
		return m_bIsLeaf;
	}

	virtual bool Insert( __int64 nKey ) = 0;

	virtual void print() = 0;
};
