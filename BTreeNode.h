

#pragma once

class BTreeNode {

protected:
	BTreeNode() {
	}

public:

	virtual ~BTreeNode() {
	}

	virtual bool HasKey( __int64 nKey ) = 0;
};
