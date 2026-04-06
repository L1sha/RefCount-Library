#pragma once

#include "RCIPtr.h"
#include <utility>

template <typename T>
class RCWrapper {
public:
	RCWrapper() : m_pValue( new T ) {}
	RCWrapper( const T& value ) : m_pValue( new T( value ) ) {}
	RCWrapper& operator=( const T& value ) {
		m_pValue = new T( value );
		return *this;
	}
	RCWrapper( T&& value ) : m_pValue( new T( std::move( value ) ) ) {}
	RCWrapper& operator=( T&& value ) {
		m_pValue = new T( std::move( value ) );
		return *this;
	}
	// Rule of Zero

private:
	RCIPtr<T> m_pValue;
};