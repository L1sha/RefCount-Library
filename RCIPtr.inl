#pragma once
#include "RCIPtr.h"
#include "RCObj.h"

template <typename T>
struct RCIPtr<T>::CountHolder : public RCObj {
	CountHolder(T* pData = nullptr) : m_pData( pData ) {}
	~CountHolder() {
		if ( m_pData )
			delete m_pData;
	}
	T* m_pData;
};

template <typename T>
void RCIPtr<T>::Init() {
	if ( !m_pCountHolder )
		return;

	if ( !m_pCountHolder->IsShareable() ) {
		T* pData = m_pCountHolder->m_pData;
		m_pCountHolder = new CountHolder( pData ? new T( *pData ) : nullptr );
	}

	m_pCountHolder->AddRef();
}

template <typename T>
void RCIPtr<T>::MakeCopy() {
	if ( !m_pCountHolder )
		return;

	if ( m_pCountHolder->IsShared() ) {
		T* pData = m_pCountHolder->m_pData;
		m_pCountHolder->Release();
		m_pCountHolder = new CountHolder( pData ? new T( *pData ) : nullptr );
		m_pCountHolder->AddRef();
	}

	m_pCountHolder->MarkUnshareable();
}

template <typename T>
RCIPtr<T>::RCIPtr( T* pData ) : m_pCountHolder( new CountHolder( pData ) ) {
	Init();
}

template <typename T>
RCIPtr<T>::RCIPtr( const RCIPtr<T>& rhs ) : m_pCountHolder( rhs.m_pCountHolder ) {
	Init();
}

template <typename T>
RCIPtr<T>& RCIPtr<T>::operator=( const RCIPtr<T>& rhs ) {
	if ( m_pCountHolder != rhs.m_pCountHolder ) {
		if ( m_pCountHolder )
			m_pCountHolder->Release();
		m_pCountHolder = rhs.m_pCountHolder;
		Init();
	}
	return *this;
}

template <typename T>
RCIPtr<T>::RCIPtr( RCIPtr<T>&& rhs ) noexcept : m_pCountHolder( rhs.m_pCountHolder ) {
	rhs.m_pCountHolder = nullptr;
}

template <typename T>
RCIPtr<T>& RCIPtr<T>::operator=( RCIPtr<T>&& rhs ) noexcept {
	if ( m_pCountHolder != rhs.m_pCountHolder ) {
		if ( m_pCountHolder )
			m_pCountHolder->Release();
		m_pCountHolder = rhs.m_pCountHolder;
		rhs.m_pCountHolder = nullptr;
	}
}

template <typename T>
const T* RCIPtr<T>::operator->() const {
	return m_pCountHolder ? m_pCountHolder->m_pData : nullptr;
}

template <typename T>
T* RCIPtr<T>::operator->() {
	if ( !m_pCountHolder )
		return nullptr;
	MakeCopy();
	return m_pCountHolder->m_pData;
}

template <typename T>
const T& RCIPtr<T>::operator*() const {
	return *m_pCountHolder->m_pData;
}

template <typename T>
T& RCIPtr<T>::operator*() {
	MakeCopy();
	return *m_pCountHolder->m_pData;
}

template <typename T>
RCIPtr<T>::~RCIPtr() {
	if ( m_pCountHolder )
		m_pCountHolder->Release();
}