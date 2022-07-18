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
		typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
		typedef typename iterator_traits<Iterator>::value_type value_type;
		typedef typename iterator_traits<Iterator>::difference_type differnce_type;
		typedef typename iterator_traits<Iterator>::pointer pointer;
		typedef typename iterator_traits<Iterator>::reference reference;

	private:
		iterator_type _base_iter;

	public:
		reverse_iterator() : _base_iter(){};
		explicit reverse_iterator(iterator_type it) : _base_iter(it){};
		template <class Iter>
		reverse_iterator(const reverse_iterator<Iter> &rev_it) : _base_iter(rev_it.base()){};
		virtual ~reverse_iterator(){};

		iterator_type base()
		{
			return this->_base_iter;
		}

		// operator
		reference operator*() const
		{
			iterator_type tmp(this->_base_iter);
			return *(--tmp);
		}

		pointer operator+(differnce_type n)
		{
			return reverse_iterator(this->_base_iter - n);
		}

		reverse_iterator operator++()
		{
			--this->_base_iter;
			return *this;
		}
		reverse_iterator operator++(int)
		{
			reverse_iterator tmp = *this;
			--this->_base_iter;
			return tmp;
		}

		reverse_iterator operator+=(differnce_type n)
		{
			this->_base_iter -= n;
			return *this;
		}

		pointer operator-(differnce_type n)
		{
			return reverse_iterator(this->_base_iter + n);
		}

		reverse_iterator operator--()
		{
			++_base_iter;
			return *this;
		}
		reverse_iterator operator--(int)
		{
			reverse_iterator tmp = *this;
			++this->_base_iter;
			return tmp;
		}

		reverse_iterator operator-=(differnce_type n)
		{
			this->_base_iter += n;
			return *this;
		}

		pointer operator->() const
		{
			return &(this->operator*());
		}

		reference operator[](differnce_type n)
		{
			return (this->_base_iter[-n - 1]);
		}
	};

	// relational operators
	template <class Iterator1, class Iterator2>
	bool operator==(const reverse_iterator<Iterator1> &lhs,
					const reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() == rhs.base());
	};

	template <class Iterator1, class Iterator2>
	bool operator!=(const reverse_iterator<Iterator1> &lhs,
					const reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() != rhs.base());
	};

	template <class Iterator1, class Iterator2>
	bool operator<(const reverse_iterator<Iterator1> &lhs,
				   const reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() > rhs.base());
	};

	template <class Iterator1, class Iterator2>
	bool operator<=(const reverse_iterator<Iterator1> &lhs,
					const reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() >= rhs.base());
	};

	template <class Iterator1, class Iterator2>
	bool operator>(const reverse_iterator<Iterator1> &lhs,
				   const reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() < rhs.base());
	};

	template <class Iterator1, class Iterator2>
	bool operator>=(const reverse_iterator<Iterator1> &lhs,
					const reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() <= rhs.base());
	};

	template <class Iterator>
	reverse_iterator<Iterator> operator+(
		typename reverse_iterator<Iterator>::difference_type n,
		const reverse_iterator<Iterator> &rev_it)
	{
		return rev_it + n;
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(
		const reverse_iterator<Iterator> &lhs,
		const reverse_iterator<Iterator> &rhs)
	{
		return rhs.base() - lhs.base();
	}
}

#endif