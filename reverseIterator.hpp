#ifndef REVERSEITERATOR_HPP
#define REVERSEITERATOR_HPP

#include "iterator.hpp"

namespace ft
{
	template <class Iterator>
	class reverse_iterator
	{
	public:
		typedef Iterator iterator_type;
		typedef typename iterator_traits<Iterator>::value_type value_type;
		typedef typename iterator_traits<Iterator>::difference_type difference_type;
		typedef typename iterator_traits<Iterator>::pointer pointer;
		typedef typename iterator_traits<Iterator>::reference reference;
		typedef typename iterator_traits<Iterator>::iterator_category iterator_category;

	private:
		iterator_type _base_iter;

		/*
		** ------------------------------- CONSTRUCTOR --------------------------------
		*/

	public:
		// default constructor
		reverse_iterator() : _base_iter(iterator_type()) {}

		// initialization
		explicit reverse_iterator(iterator_type it) : _base_iter(it) {}

		// copy constructor
		template <class Iter>
		reverse_iterator(const reverse_iterator<Iter> &rev_it) : _base_iter(rev_it.base()) {}

		/*
		** -------------------------------- Getter ---------------------------------
		*/

		iterator_type base() const
		{
			return iterator_type(this->_base_iter);
		}

		/*
		** ------------------------------- Operators --------------------------------
		*/

		// template <class Iter>
		// reverse_iterator &operator=(const reverse_iterator<Iter> &rev_it) 
		// {

		// }

		reference operator*() const
		{
			iterator_type copy_iter(this->_base_iter);
			--copy_iter;
			return *copy_iter;
		}

		reverse_iterator operator+(difference_type n) const
		{
			return reverse_iterator(this->_base_iter - n);
		}

		reverse_iterator &operator++()
		{
			this->_base_iter--;
			return *this;
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator tmp = *this;
			++(*this);
			return tmp;
		}

		reverse_iterator &operator+=(difference_type n)
		{
			this->_base_iter -= n;
			return *this;
		}

		reverse_iterator operator-(difference_type n) const
		{
			return reverse_iterator(this->_base_iter + n);
		}

		reverse_iterator &operator--()
		{
			this->_base_iter++;
			return *this;
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator tmp = *this;
			--(*this);
			return tmp;
		}

		reverse_iterator &operator-=(difference_type n)
		{
			this->_base_iter += n;
			return *this;
		}

		pointer operator->() const
		{
			return &(this->operator*());
		}

		reference operator[](difference_type n) const
		{
			return this->_base_iter[-n - 1];
		}
	};

	template <class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &rev_it)
	{
		return rev_it + n;
	}

	template <class Iterator, class Iterator2>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return rhs.base() - lhs.base();
	}

	template <class Iterator, class Iterator2>
	bool operator==(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <class Iterator, class Iterator2>
	bool operator!=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return lhs.base() != rhs.base();
	}

	template <class Iterator, class Iterator2>
	bool operator<(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return lhs.base() > rhs.base();
	}

	template <class Iterator, class Iterator2>
	bool operator<=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template <class Iterator, class Iterator2>
	bool operator>(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return lhs.base() < rhs.base();
	}

	template <class Iterator, class Iterator2>
	bool operator>=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return lhs.base() <= rhs.base();
	}
}

#endif