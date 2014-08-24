

class BTreeIndexNode {
	// key is 8 bytes
	// page number is 4 bytes
	// 8n + 4*(n+1) = 8192
	// 8n +4n +4 = 8192
	// 12n = 8188
	// n = 682 
	static const int nOrder = 682;
	__int64 m_key[nOrder];
	int m_pageNumber[nOrder+1];
	int m_nKeys;

public:
	BTreeIndexNode() {
		m_nKeys = 0;
		for ( int n = 0; n < nOrder; n++ ) {
			m_pageNumber[n] = -1;
			m_key[n] = 0;
		}
		m_pageNumber[nOrder] = -1;
	}
};