
#include <string.h>
#include <stdlib.h>
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "common.h"

class CPagedFile {
	const char* m_pstrFileName;
	int m_nPageSize;
	int m_handle;

public:
	CPagedFile( const char* pstrFileName, int nPageSize ) {
		m_handle = ::_open( pstrFileName, _O_BINARY | _O_RANDOM | _O_RDWR );
		if ( m_handle == -1 ) {
			throw errno;
		}
		m_pstrFileName = ::_strdup( pstrFileName );
		m_nPageSize = nPageSize;
	}

	CPagedFile( const char* pstrFileName, int nPageSize, int nIntialPages ) {
		m_handle = ::_open( pstrFileName, _O_BINARY | _O_RANDOM | _O_RDWR | _O_CREAT,  _S_IREAD | _S_IWRITE );
		if ( m_handle == -1 ) {
			throw errno;
		}

		m_nPageSize = nPageSize;
		m_pstrFileName = ::_strdup( pstrFileName );

		byte* p = new byte[m_nPageSize];
		::memset( p, 0, m_nPageSize );

		for ( int n = 0; n < nIntialPages; n++ ) {
			int nWritten = ::_write( m_handle, p, m_nPageSize );
			if ( nWritten != m_nPageSize ) {
				::_close( m_handle );
				::_unlink( pstrFileName );
				delete [] p;
				throw -1;
			}
		}

		::_lseek( m_handle, 0, 0 );
		delete [] p;
	}

	bool ReadPage( int nPage, byte* pBytes ) {
		int location = ::_lseek( m_handle, m_nPageSize * nPage, 0 );
		if ( location != nPage * m_nPageSize ) {
			return false;
		}
		int n = ::_read( m_handle, pBytes, m_nPageSize );
		if ( n != m_nPageSize ) {
			return false;
		}

		return true;
	}

	bool WritePage( int nPage, byte* pBytes ) {
		int location = ::_lseek( m_handle, m_nPageSize * nPage, 0 );
		if ( location != nPage * m_nPageSize ) {
			return false;
		}
		int n = ::_write( m_handle, pBytes, m_nPageSize );
		if ( n != m_nPageSize ) {
			return false;
		}
		
		return true;
	}

	void Close() {
		if ( m_handle != 0 ) {
			::_close( m_handle );
		}
		m_handle = 0;
	}

	~CPagedFile() {
		Close();
		::free( (void*) m_pstrFileName );
	}
};