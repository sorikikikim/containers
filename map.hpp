#ifndef MAP_HPP
#define MAP_HPP

#include <map>
#include "vector.hpp"

namespace ft
{
	template <
		class Key,									// map::key_type
		class T,									// map::mapped_type
		class Compare = ft::less<Key>,				// map::key_compare
		class Alloc = std::allocator<pair<const Key, T> > // map::allocator_type
		>
	class map
	{
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const key_type, mapped_type> value_type;
		typedef Compare key_compare;
		typedef Allocator allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename allocator_type::size_type size_type;
		typedef typename allocator_type::difference_type difference_type;
		typedef ft::random_access_iterator iterator;
		typedef ft::random_access_iterator const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

		explicit map(const key_compare &comp = key_compare(),
					 const allocator_type &alloc = allocator_type()) {}

		template <class InputIterator>
		map(InputIterator first, InputIterator last,
			const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type()) {}

		map(const map &x) {}

		~map() {}

	private:
		class value_compare
		{ // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
			friend class map;

		protected:
			key_compare comp;
			value_compare(Compare c) : comp(c) {} // constructed with map's comparison object
		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator()(const value_type &x, const value_type &y) const
			{
				return comp(x.first, y.first);
			}
		}

	public:
		/*
		** --------------------------------- iterators ---------------------------------
		*/

		iterator begin();
		const_iterator begin() const;

		iterator end();
		const_iterator end() const;

		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;

		reverse_iterator rend();
		const_reverse_iterator rend() const;

		/*
		** --------------------------------- capacity ---------------------------------
		*/
		bool empty() const;
		size_type size() const;
		size_type max_size() const;

		/*
		** ------------------------------ element access ------------------------------
		*/
		mapped_type &operator[](const key_type &k);

		/*
		** --------------------------------- modifiers ---------------------------------
		*/

		pair<iterator, bool> insert(const value_type &val);
		iterator insert(iterator position, const value_type &val);
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last);

		void erase(iterator position);
		size_type erase(const key_type &k);
		void erase(iterator first, iterator last);

		void swap(map &x);

		void clear();

		key_compare key_comp() const
		{
			return this->_comp;
		}

		value_compare value_comp() const
		{
			return value_comp(key_comp());
		}

		iterator find(const key_type &k);
		const_iterator find(const key_type &k) const;

		size_type count(const key_type &k) const;

		iterator lower_bound(const key_type &k);
		const_iterator lower_bound(const key_type &k) const;

		iterator upper_bound(const key_type &k);
		const_iterator upper_bound(const key_type &k) const;

		pair<const_iterator, const_iterator> equal_range(const key_type &k) const;
		pair<iterator, iterator> equal_range(const key_type &k);

		allocator_type get_allocator() const
		{
		}
	};
}

#endif