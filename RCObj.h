#pragma once

class RCObj {
protected:
	RCObj() : m_nRefCount{ 0 }, m_bShareable{ true } {}
	RCObj( const RCObj& rhs ) : m_nRefCount{ 0 }, m_bShareable{ true } {}
	RCObj& operator=( const RCObj& rhs ) { return *this; }
	RCObj( RCObj&& rhs ) noexcept : m_nRefCount{ 0 }, m_bShareable{ true } {}
	RCObj& operator=( RCObj&& rhs ) noexcept { return *this; }
	virtual ~RCObj() = 0;

public:
	void AddRef() { ++m_nRefCount; }
	void Release() { if ( --m_nRefCount == 0 ) delete this; }
	void MarkUnshareable() { m_bShareable = false; }
	bool IsShareable() const { return m_bShareable; }
	bool IsShared() const { return m_nRefCount > 1; }

private:
	unsigned int m_nRefCount;
	bool m_bShareable;
};