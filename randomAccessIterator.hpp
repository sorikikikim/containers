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

		/*
		** ------------------------------- CONSTRUCTOR --------------------------------
		*/

		//default constructor
		random_access_iterator() : _ptr(0) {}

		//copy constructor
		template <class Other>
		random_access_iterator(const random_access_iterator<Other> &src) : _ptr(src.getPtr()) {}

		random_access_iterator(const random_access_iterator &src) : _ptr(src.getPtr()) {}

		//initialization
		random_access_iterator(pointer ptr) : _ptr(ptr) {}

		/*
		** ------------------------------- DESTRUCTOR --------------------------------
		*/

		//destructor
		~random_access_iterator(){};

		/*
		** -------------------------- Assignment Operator -----------------------------
		*/

		//assignment operator overloading
		random_access_iterator &operator=(const random_access_iterator &src)
		{
			if (this != &src)
				this->_ptr = src.getPtr();
			return *this;
		}

		/*
		** -------------------------------- Getter ---------------------------------
		*/

		pointer getPtr() const
		{
			return this->_ptr;
		}

		/*
		** ------------------------------- Operators --------------------------------
		*/

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
			return &(operator*()); 
		}

		reference operator[](difference_type n) const
		{
			return *(this->_ptr + n);
		}

		random_access_iterator &operator+=(difference_type n)
		{
			this->_ptr += n;
			return *this;
		}

		random_access_iterator operator+(difference_type n)
		{
			return random_access_iterator(this->_ptr + n);
		}

		random_access_iterator &operator-=(difference_type n)
		{
			this->_ptr -= n;
			return *this;
		}

		random_access_iterator operator-(difference_type n)
		{
			return random_access_iterator(this->_ptr - n);
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


	template <class T>
	random_access_iterator<T> operator+(
		typename random_access_iterator<T>::difference_type n,
		random_access_iterator<T> iter)
	{
		return iter + n;
	}


	template <class A, class B>
	typename random_access_iterator<A>::difference_type operator-(
		random_access_iterator<A> lhs,
		random_access_iterator<B> rhs)
	{
		return lhs.getPtr() - rhs.getPtr();
	}

	template <class T>
	random_access_iterator<T> operator+(random_access_iterator<T> lhs, typename random_access_iterator<T>::difference_type rhs)
	{
		lhs += rhs;
		return lhs;
	}


	template <class T>
	random_access_iterator<T> operator-(random_access_iterator<T> lhs, typename random_access_iterator<T>::difference_type rhs)
	{
		lhs -= rhs;
		return lhs;
	}
}

#endif