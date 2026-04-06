#include "String.h"
#include <cstring>

struct String::StringValue : public RCObj {
	StringValue( const char* pStr ) {
		m_pStr = new char[ strlen( pStr ) + 1 ];
		strcpy_s( m_pStr, strlen( pStr ) + 1, pStr );
	}
	StringValue( const StringValue& rhs ) {
		m_pStr = new char[ strlen( rhs.m_pStr ) + 1 ];
		strcpy_s( m_pStr, strlen( rhs.m_pStr ) + 1, rhs.m_pStr);
	}
	StringValue( StringValue&& rhs ) noexcept : m_pStr( rhs.m_pStr ) { 
		rhs.m_pStr = nullptr; 
	}
	~StringValue() { 
		delete[] m_pStr; 
	}
	
	char* m_pStr;
};

String::String( const char* pStr ) : m_pValue( new StringValue( pStr ) ) {}
String::String( const String& rhs ) = default;
String& String::operator=( const String& rhs ) = default;
String::String( String&& rhs ) noexcept = default;
String& String::operator=( String&& rhs ) noexcept = default;
String::~String() = default;

const char& String::operator[]( size_t nIdx ) const {
	return m_pValue->m_pStr[nIdx];
}

char& String::operator[]( size_t nIdx ) {
	if ( m_pValue->IsShared() )
		m_pValue = new StringValue( m_pValue->m_pStr );	// StringValue 생성 -> RCPtr 임시 객체 생성 -> 이동 대입 연산자 호출
	
	m_pValue->MarkUnshareable();

	return m_pValue->m_pStr[nIdx];
}