
#include <unordered_map>
#include "BTreeNode.h"

class BTree {

	std::unordered_map<int, BTreeNode> m_pageCache;

public:
	BTree() {
		m_pageCache = new std::unordered_map<int, BTreeNode>();
	}
};