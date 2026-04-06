#pragma once
// #include <type_traits>
#include "RCObj.h"

// T는 RCObj를 상속해야 한다. 이러한 제한 사항을
// C++17까지는 SFINAE를 이용해서 구현, C++20에서는 required를 이용해서 구현할 수 있다
// 그러나 이 과정에서, RCPtr이 사용할 T(현재 예제의 경우 String::StringValue)가 Complete Type이어야 한다
// String::StringValue의 구현을 String.cpp에 숨기고 있기 때문에 이는 불가능하다
template<typename T>
class RCPtr {
public:
	RCPtr( T* pData = nullptr ) : m_pData( pData ) { Init(); }
	RCPtr( const RCPtr& rhs ) : m_pData( rhs.m_pData ) { Init(); }
	RCPtr& operator=( const RCPtr& rhs );
	RCPtr( RCPtr&& rhs ) noexcept : m_pData( rhs.m_pData ) { rhs.m_pData = nullptr; }
	RCPtr& operator=( RCPtr&& rhs ) noexcept;
	~RCPtr();

	T* operator->() const { return m_pData; }
	T& operator*() const { return *m_pData; }

private:
	void Init();

	T* m_pData;
};

#include "RCPtr.inl"