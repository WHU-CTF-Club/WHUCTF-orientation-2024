#pragma once

#include <utility>

#include <Windows.h>

template<typename T>
struct HandleTraits
{
	using type = T;

	static constexpr T invalid_value() noexcept
	{
		return T{};
	}
};

struct ServiceHandleTraits : public HandleTraits<SC_HANDLE>
{
	static void close(SC_HANDLE handle) noexcept
	{
		CloseServiceHandle(handle);
	}
};

struct PrivilegeTokenHandleTraits : public HandleTraits<HANDLE>
{
	static void close(HANDLE handle) noexcept
	{
		CloseHandle(handle);
	}
};

struct ResourceHandleTraits : public HandleTraits<HGLOBAL>
{
	static void close(HGLOBAL handle) noexcept
	{
		CloseHandle(handle);
	}
};

struct LibraryHandleTraits : public HandleTraits<HMODULE>
{
	static void close(HMODULE handle) noexcept
	{
		FreeLibrary(handle);
	}
};

template <typename Traits>
struct Handle
{
	using value_type = typename Traits::type;

	Handle() noexcept = default;

	explicit Handle(value_type value) noexcept
		: value_{ value }
	{ }

	// Not copyable
	Handle(Handle const&) = delete;
	Handle& operator= (Handle const&) = delete;

	// Movable
	Handle(Handle&& another) noexcept
		: value_{ another.release() }
	{ }
	Handle& operator= (Handle&& other) noexcept
	{
		this->reset(other.release());
		return *this;
	}

	~Handle() noexcept
	{
		if (*this)
			Traits::close(this->value_);
	}

	explicit operator bool() const noexcept
	{
		return this->value_ != Traits::invalid_value();
	}

	operator const value_type& () const noexcept
	{
		return this->value_;
	}

	operator value_type& () noexcept
	{
		return this->value_;
	}

	const value_type& get() const noexcept
	{
		return this->value_;
	}

	value_type& get() noexcept
	{
		return this->value_;
	}

	value_type release() noexcept {
		return std::exchange(this->value_, Traits::invalid_value());
	}

	void reset(value_type value) noexcept
	{
		if (*this)
			Traits::close(this->value_);
		this->value_ = value;
	}

	void swap(Handle& other) noexcept
	{
		using std::swap;
		swap(this->Value, other.Value);
	}

	friend void swap(Handle& lhs, Handle& rhs) noexcept
	{
		lhs.swap(rhs);
	}

private:
	value_type value_{ Traits::invalid_value() };
};

using ServiceHandle = Handle<ServiceHandleTraits>;
using PrivilegeTokenHandle = Handle<PrivilegeTokenHandleTraits>;
using ResourceHandle = Handle<ResourceHandleTraits>;
using LibraryHandle = Handle<LibraryHandleTraits>;
