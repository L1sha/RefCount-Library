#include "String.h"
#include <cstring>

struct String::StringValue : public RCObj {
	StringValue( const char* pStr ) {
		m_pStr = new char[ strlen( pStr ) + 1 ];
		strcpy_s( m_pStr, strlen( pStr ) + 1, pStr );
	}
	StringValue( const StringValue& rhs ) {
		m_pStr = new char[ strlen( rhs.m_pStr ) + 1 ];
		strcpy_s( m_pStr, strlen( rhs.m_pStr ) + 1, rhs.m_pStr );
	}
	StringValue( StringValue&& rhs ) noexcept : m_pStr( rhs.m_pStr ) {
		rhs.m_pStr = nullptr;
	}
	~StringValue() {
		delete[] m_pStr;
	}

	char* m_pStr;
};

String::CharProxy& String::CharProxy::operator=( char c ) { // 좌항
	if ( m_rString.m_pValue->IsShared() )
		m_rString.m_pValue = new StringValue( m_rString.m_pValue->m_pStr );	// StringValue 생성 -> RCPtr 임시 객체 생성 -> 이동 대입 연산자 호출

	m_rString.m_pValue->m_pStr[ m_nIdx ] = c;

	return *this;
}

String::CharProxy& String::CharProxy::operator=( const String::CharProxy& rhs ) { // 좌항
	if ( m_rString.m_pValue->IsShared() )
		m_rString.m_pValue = new StringValue( m_rString.m_pValue->m_pStr );

	m_rString.m_pValue->m_pStr[ m_nIdx ] = rhs.m_rString.m_pValue->m_pStr[ rhs.m_nIdx ];

	return *this;
}

char* String::CharProxy::operator&() {
	if ( m_rString.m_pValue->IsShared() )
		m_rString.m_pValue = new StringValue( m_rString.m_pValue->m_pStr );

	m_rString.m_pValue->MarkUnshareable(); // & 연산자를 통해 얻은 포인터로 수정할 수 있으므로..

	return &m_rString.m_pValue->m_pStr[ m_nIdx ];
}

const char* String::CharProxy::operator&() const {
	return &m_rString.m_pValue->m_pStr[ m_nIdx ];
}

String::CharProxy::operator char&() {
	if ( m_rString.m_pValue->IsShared() )
		m_rString.m_pValue = new StringValue( m_rString.m_pValue->m_pStr );

	m_rString.m_pValue->MarkUnshareable(); // 반환된 참조를 이용해 수정할 수 있으므로..

	return m_rString.m_pValue->m_pStr[ m_nIdx ];
}

String::CharProxy::operator char() const { // 우항
	return m_rString.m_pValue->m_pStr[ m_nIdx ];
}

String::String( const char* pStr ) : m_pValue( new StringValue( pStr ) ) {}
String::String( const String& rhs ) = default;
String& String::operator=( const String& rhs ) = default;
String::String( String&& rhs ) noexcept = default;
String& String::operator=( String&& rhs ) noexcept = default;
String::~String() = default;

const String::CharProxy String::operator[]( int nIdx ) const {
	return String::CharProxy( const_cast<String&>( *this ), nIdx );
}

String::CharProxy String::operator[]( int nIdx ) {
	return String::CharProxy( *this, nIdx );
}
