#pragma once
#include "RCPtr.h"

template<typename T>
void RCPtr<T>::Init() {
	if ( !m_pData )
		return;

	if ( !m_pData->IsShareable() )
		m_pData = new T( *m_pData );

	m_pData->AddRef();
}

template<typename T>
RCPtr<T>& RCPtr<T>::operator=( const RCPtr<T>& rhs ) {
	if ( m_pData != rhs.m_pData ) {
		if ( m_pData )
			m_pData->Release();
		m_pData = rhs.m_pData;
		Init();
	}
	return *this;
}

template<typename T>
RCPtr<T>& RCPtr<T>::operator=( RCPtr<T>&& rhs ) noexcept {
	if ( m_pData != rhs.m_pData ) {
		if ( m_pData )
			m_pData->Release();
		m_pData = rhs.m_pData;
		rhs.m_pData = nullptr;
	}
	return *this;
}

template<typename T>
RCPtr<T>::~RCPtr() {
	if ( m_pData )
		m_pData->Release();
}