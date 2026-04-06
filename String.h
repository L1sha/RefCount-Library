#pragma once

#include "RCPtr.h"

class String {
public:
	String( const char *pStr = "" );
	String( const String& rhs );
	String& operator=( const String& rhs );
	String( String&& rhs ) noexcept;
	String& operator=( String&& rhs ) noexcept;
	~String();
	// 전부 default를 사용할 수 있지만, StringValue의 구현이 String.cpp에 있어서 String.h에선 선언한 뒤 String.cpp에서 default로 정의한다

	const char& operator[]( size_t nIdx ) const;
	char& operator[]( size_t nIdx );

private:
	struct StringValue;
	RCPtr<StringValue> m_pValue;
};