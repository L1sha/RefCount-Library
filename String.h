#pragma once

#include "RCPtr.h"

class String {
public:
	String( const char pStr = "" );
	String( const String& rhs );
	String& operator=( const String& rhs );
	String( String&& rhs ) noexcept;
	String& operator=( String&& rhs ) noexcept;
	~String();
	// 전부 default를 사용할 수 있지만, StringValue의 구현이 String.cpp에 있어서 String.h에선 선언한 뒤 String.cpp에서 default로 정의한다

	class CharProxy {
	public:
		CharProxy( String& rString, int nIdx ) : m_rString( rString ), m_nIdx( nIdx ) {}
		CharProxy& operator=( char c );
		CharProxy& operator=( const CharProxy& rhs );
		char* operator&();
		const char* operator&() const;
		operator char&();
		operator char() const;
	private:
		String& m_rString;
		int m_nIdx;
	};

	const CharProxy operator[]( int nIdx ) const;
	CharProxy operator[]( int nIdx );

private:
	friend class CharProxy;
	struct StringValue;
	RCPtr<StringValue> m_pValue;
};
