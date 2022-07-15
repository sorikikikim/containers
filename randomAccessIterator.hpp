#ifndef RANDOMACCESSITERATOR_HPP
#define RANDOMACCESSITERATOR_HPP

#include <iostream>
#include "iterator.hpp"

namespace ft
{
	template <typename T>
	class random_access_iterator
	{
	public:
		typedef typename iterator_traits<T *>::value_type value_type;
		typedef typename iterator_traits<T *>::difference_type difference_type;
		typedef typename iterator_traits<T *>::pointer pointer;
		typedef typename iterator_traits<T *>::reference reference;
		typedef typename iterator_traits<T *>::iterator_category iterator_category;

		random_access_iterator() : _ptr(0) {}
		random_access_iterator(const random_access_iterator &src) : _ptr(src.getPtr()) {}
		random_access_iterator(pointer ptr) : _ptr(ptr) {}
		random_access_iterator &operator=(const random_access_iterator &src)
		{
			if (this != &src)
				this->_ptr = src.getPtr();
			return *this;
		}
		~random_access_iterator(){};

		random_access_iterator &operator++()
		{
			this->_ptr++;
			return *this;
		}

		random_access_iterator operator++(int)
		{
			random_access_iterator tmp(*this);
			this->_ptr++;
			return tmp;
		}

		random_access_iterator &operator--()
		{
			this->_ptr--;
			return *this;
		}

		random_access_iterator operator--(int)
		{
			random_access_iterator tmp(*this);
			this->_ptr--;
			return tmp;
		}

		reference operator*() const
		{
			return *this->_ptr;
		}

		pointer operator->() const
		{
			return this->_ptr;
		}

		reference operator[](difference_type n) const
		{
			return *(this->_ptr + n);
		}

		random_access_iterator &operator+=(difference_type rhs)
		{
			this->_ptr += rhs;
			return *this;
		}

		random_access_iterator &operator-=(difference_type rhs)
		{
			this->_ptr -= rhs;
			return *this;
		}

		pointer getPtr() const
		{
			return this->_ptr;
		}

	private:
		pointer _ptr;
	};

	template <class A, class B>
	bool operator==(const random_access_iterator<A> &lhs,
					const random_access_iterator<B> &rhs)
	{
		return lhs.getPtr() == rhs.getPtr();
	}

	template <class A, class B>
	bool operator!=(const random_access_iterator<A> &lhs,
					const random_access_iterator<B> &rhs)
	{
		return !operator==(lhs, rhs);
	}

	template <class A, class B>
	bool operator<(const random_access_iterator<A> &lhs,
				   const random_access_iterator<B> &rhs)
	{
		return lhs.getPtr() < rhs.getPtr();
	}

	template <class A, class B>
	bool operator>(const random_access_iterator<A> &lhs,
				   const random_access_iterator<B> &rhs)
	{
		return operator<(rhs, lhs);
	}

	template <class A, class B>
	bool operator<=(const random_access_iterator<A> &lhs,
					const random_access_iterator<B> &rhs)
	{
		return !operator>(lhs, rhs);
	}

	template <class A, class B>
	bool operator>=(const random_access_iterator<A> &lhs,
					const random_access_iterator<B> &rhs)
	{
		return !operator<(lhs, rhs);
	}

	template <class A, class B>
	typename random_access_iterator<A>::difference_type operator-(
		random_access_iterator<B> lhs,
		random_access_iterator<B> rhs)
	{
		return lhs.getPtr() - rhs.getPtr();
	}

	template <class T>
	random_access_iterator<T> operator+(
		random_access_iterator<T> iter,
		typename random_access_iterator<T>::difference_type n)
	{
		iter += n;
		return iter;
	}

	template <class T>
	random_access_iterator<T> operator+(
		typename random_access_iterator<T>::difference_type n,
		random_access_iterator<T> iter)
	{
		iter += n;
		return iter;
	}

	template <class T>
	random_access_iterator<T> operator-(
		random_access_iterator<T> iter,
		typename random_access_iterator<T>::difference_type n)
	{
		iter -= n;
		return iter;
	}

	template <class T>
	random_access_iterator<T> operator-(
		typename random_access_iterator<T>::difference_type n,
		random_access_iterator<T> iter)
	{
		iter -= n;
		return iter;
	}
}

#endif