#pragma once

template <typename T>
class RCIPtr {
public:
	RCIPtr( T* pData = nullptr );
	RCIPtr( const RCIPtr& rhs );
	RCIPtr& operator=( const RCIPtr& rhs );
	RCIPtr( RCIPtr&& rhs ) noexcept;
	RCIPtr& operator=( RCIPtr&& rhs ) noexcept;
	~RCIPtr();

	const T* operator->() const;
	T* operator->();
	const T& operator*() const;
	T& operator*();

private:
	void Init();
	void MakeCopy();

	struct CountHolder;
	CountHolder* m_pCountHolder;
};

#include "RCIPtr.inl"