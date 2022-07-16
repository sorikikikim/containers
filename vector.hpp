#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <vector>
#include "randomAccessIterator.hpp"
#include "reverseIterator.hpp"
#include "utils.hpp"
#include <stdexcept>

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
	public:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef ft::random_access_iterator<value_type> iterator;
		typedef ft::random_access_iterator<const value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
		typedef typename allocator_type::size_type size_type;

	private:
		pointer _data;
		size_type _size;
		size_type _capacity;
		allocator_type _alloc;

	public:
		/*
		** ------------------------------- CONSTRUCTOR --------------------------------
		*/
		// default
		explicit vector(const allocator_type &alloc = allocator_type())
		{
			this->_size = 0;
			this->_capacity = 0;
			this->_alloc = alloc;
			this->_data = 0;
		}

		// fill
		explicit vector(size_type n, const value_type &val = value_type(),
						const allocator_type &alloc = allocator_type())
		{
			this->_size = n;
			this->_capacity = n;
			this->_alloc = alloc;
			this->_data = this->_alloc.allocate(this->_capacity);
			for (size_type i = 0; i < this->_size; i++)
				this->_alloc.construct(&this->_data[i], val);
		}

		// range
		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
			   typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0) : _alloc(alloc)
		{
			this->_size = 0;
			for (InputIterator it = first; it != last; it++)
				this->_size++;
			this->_capacity = this->_size;
			this->_alloc = alloc;
			this->_data = this->_alloc.allocate(this->_capacity);
			size_type i = 0;
			for (InputIterator it = first; it != last; it++)
			{
				this->_alloc.construct(&this->_data[i], *it);
				i++;
			}
		};

		// copy
		vector(const vector &x)
		{
			this->_size = x.size();
			this->_capacity = x.capacity();
			this->_alloc = x.get_allocator();
			this->_data = this->_alloc.allocate(this->_capacity);
			for (size_type i = 0; i < this->_size; i++)
				this->_alloc.construct(&this->_data[i], x._data[i]);
		}

		/*
		** ------------------------------- DESTRUCTOR --------------------------------
		*/

		~vector()
		{
			if (this->_data)
			{
				for (size_type i = 0; i < this->_size; i++)
					this->_alloc.destroy(&this->_data[i]);
				this->_alloc.deallocate(this->_data, this->_capacity);
			}
		}

		/*
		** --------------------------------- operator= ---------------------------------
		*/

		vector &operator=(const vector &x)
		{
			if (this != &x)
			{
				if (this->_data)
				{
					for (size_type i = 0; i < this->_size; i++)
						this->_alloc.destroy(&this->_data[i]);
					this->_alloc.deallocate(this->_data, this->_capacity);
				}
				this->_size = x.size();
				this->_capacity = x.capacity();
				this->_data = this->_alloc.allocate(this->_capacity);
				for (size_type i = 0; i < this->_size; i++)
					this->_alloc.construct(&this->_data[i], x._data[i]);
			}
			return *this;
		}

		/*
		** --------------------------------- Iterators ---------------------------------
		*/

		iterator begin()
		{
			iterator it(this->_data);
			return it;
		}

		const_iterator begin() const
		{
			const_iterator it(this->_data);
			return it;
		}

		iterator end()
		{
			if (this->empty())
				return this->begin();
			iterator it(&this->_data[this->size()]);
			return it;
		}

		const_iterator end() const
		{
			if (this->empty())
				return this->begin();
			const_iterator it(&this->_data[this->size()]);
			return it;
		}

		reverse_iterator rbegin()
		{
			reverse_iterator it(this->end());
			return it;
		}

		const_reverse_iterator rbegin() const
		{
			const_reverse_iterator it(this->end());
			return it;
		}

		reverse_iterator rend()
		{
			reverse_iterator it(this->begin());
			return it;
		}

		const_reverse_iterator rend() const
		{
			const_reverse_iterator it(this->begin());
			return it;
		}

		/*
		** --------------------------------- Capacity ---------------------------------
		*/

		size_type size() const
		{
			return this->_size;
		}

		size_type max_size() const
		{
			return this->_alloc.max_size();
		}

		size_type capacity() const
		{
			return this->_capacity;
		}

		bool empty() const
		{
			return this->_size == 0 ? true : false;
		}

		void reserve(size_type n)
		{
			pointer new_data;

			if (n <= this->_capacity)
				return;
			if (n > this->max_size())
				throw std::length_error("vector");
			new_data = this->_alloc.allocate(n);
			if (this->_data)
			{
				for (size_type i = 0; i < this->_size; i++)
				{
					this->_alloc.construct(&new_data[i], this->_data[i]);
					this->_alloc.destroy(&this->_data[i]);
				}
				this->_alloc.deallocate(this->_data, this->_capacity);
			}
			this->_capacity = n;
			this->_data = new_data;
		}

		void resize(size_type n, value_type val = value_type())
		{
			for (size_type i = n; i < this->_size; i++)
				this->_alloc.destroy(&this->_data[i]);
			if (n > this->_capacity)
				this->reserve(n);
			for (size_type i = this->_size; i < n; i++)
				this->_alloc.construct(&this->_data[i], val);
			this->_size = n;
		}

		/*
		** --------------------------------- Element access ---------------------------------
		*/
		// reference by original, value by copy
		// return const = not change value -> to prevent side effect by concurrency
		// const function = not change a member variable of the class

		reference operator[](size_type n)
		{
			return this->_data[n];
		}

		const_reference operator[](size_type n) const
		{
			return this->_data[n];
		}

		reference at(size_type n)
		{
			if (n >= this->_size)
				throw std::out_of_range("vector");
			return this->_data[n];
		}

		const_reference at(size_type n) const
		{
			if (n >= this->_size)
				throw std::out_of_range("vector");
			return this->_data[n];
		}

		reference front()
		{
			return this->_data[0];
		}

		const_reference front() const
		{
			return this->_data[0];
		}

		reference back()
		{
			return this->_data[this->_size - 1];
		}

		const_reference back() const
		{
			return this->_data[this->_size - 1];
		}

		/*
		** --------------------------------- Modifiers ---------------------------------
		*/

		//[1] assign
		// range
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0)
		{
			size_type new_size = 0;

			for (InputIterator it = first; it != last; it++)
				new_size++;
			for (size_type i = 0; i < this->_size; i++)
				this->_alloc.destroy(&this->_data[i]);
			if (new_size > this->_capacity)
				this->reserve(new_size);
			size_type i = 0;
			for (InputIterator it = first; it != last; it++)
			{
				this->_alloc.construct(&this->_data[i], *it);
				i++;
			}
			this->_size = new_size;
		}

		// fill
		void assign(size_type n, const value_type &val)
		{
			for (size_type i = 0; i < this->_size; i++)
				this->_alloc.destroy(&this->_data[i]);
			if (n > this->_capacity)
				this->reserve(n);
			for (size_type i = 0; i < n; i++)
				this->_alloc.construct(&this->_data[i], val);
			this->_size = n;
		}

		//[2] push_back
		void push_back(const value_type &val)
		{
			if (this->_capacity == 0)
				this->reserve(1);
			else if (this->_size == this->_capacity)
				this->reserve(this->_capacity * 2);
			this->_alloc.construct(&this->_data[this->_size], val);
			this->_size++;
		}

		//[3] pop_back
		void pop_back()
		{
			this->_alloc.destroy(&this->_data[this->_size - 1]);
			this->_size--;
		}	

		//[4] insert
		// single element
		iterator insert(iterator position, const value_type &val)
		{
			pointer new_data;
			pointer tmp;
			size_type tmp_size = 0;
			size_type i;
			size_type new_capacity;

			if (position == this->end())
			{
				this->push_back(val);
				position = this->end() - 1;
			}
			else
			{
				for (iterator it = position; it != this->end(); it++)
					tmp_size++;
				tmp = this->_alloc.allocate(tmp_size);
				i = 0;
				for (iterator it = position; it != this->end(); it++)
				{
					this->_alloc.construct(&tmp[i], *it);
					this->_alloc.destroy(&*it);
					i++;
				}
				// reallocation
				if (this->_size == this->_capacity)
				{
					new_capacity = this->_capacity * 2;
					if (new_capacity > this->max_size())
						throw std::length_error("vector");
					new_data = this->_alloc.allocate(new_capacity);
					if (this->_data)
					{
						i = 0;
						for (iterator it = this->begin(); it != position; it++)
						{
							this->_alloc.construct(&new_data[i], *it);
							this->_alloc.destroy(&*it);
							i++;
						}
						this->_alloc.deallocate(this->_data, this->_capacity);
					}
					this->_capacity = new_capacity;
					this->_data = new_data;
					position = iterator(&this->_data[i]);
				}
				// insert
				this->_alloc.construct(&*position, val);
				this->_size++;
				// copy after insert
				i = 0;
				for (iterator it = position + 1; it != this->end(); it++)
				{
					this->_alloc.construct(&*it, tmp[i]);
					i++;
				}
				// free
				for (i = 0; i < tmp_size; i++)
					this->_alloc.destroy(&tmp[i]);
				this->_alloc.deallocate(tmp, tmp_size);
			}
			return position;
		}

		// fill
		void insert(iterator position, size_type n, const value_type &val)
		{
			pointer new_data;
			pointer tmp;
			iterator it;
			size_type tmp_size = 0;
			size_type i;
			size_type new_capacity;

			if (position == this->end())
			{
				for (size_type i = 0; i < n; i++)
					this->push_back(val);
				return;
			}
			        
			// insert
			it = position;
			for (i = 0; i < n; i++)
			{
				this->_alloc.construct(&*it, val);
				this->_size++;
				it++;
			}
			// copy after insert
			i = 0;
			for (it = position + n; it != this->end(); it++)
			{
				this->_alloc.construct(&*it, tmp[i]);
				i++;
			}
			// free
			for (i = 0; i < tmp_size; i++)
				this->_alloc.destroy(&tmp[i]);
			this->_alloc.deallocate(tmp, tmp_size);
		}

		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0)
		{
			pointer new_data;
			pointer tmp;
			iterator it;
			size_type tmp_size = 0;
			size_type i;
			size_type new_capacity;
			size_type range = 0;

			if (position == this->end())
			{
				for (InputIterator it = first; it != last; it++)
					this->push_back(*it);
				return;
			}
			for (InputIterator it = first; it != last; it++)
				range++;
			for (iterator it = position; it != this->end(); it++)
				tmp_size++;
			tmp = this->_alloc.allocate(tmp_size);
			i = 0;
			for (iterator it = position; it != this->end(); it++)
			{
				this->_alloc.construct(&tmp[i], *it);
				this->_alloc.destroy(&*it);
				i++;
			}
			// reallocation
			if ((this->_size + range) > this->_capacity)
			{
				if ((this->_size + range) > (this->_capacity * 2))
					new_capacity = this->_size + range;
				else
					new_capacity = this->_capacity * 2;
				if (new_capacity > this->max_size())
					throw std::length_error("vector");
				new_data = this->_alloc.allocate(new_capacity);
				if (this->_data)
				{
					i = 0;
					for (iterator it = this->begin(); it != position; it++)
					{
						this->_alloc.construct(&new_data[i], *it);
						this->_alloc.destroy(&*it);
						i++;
					}
					this->_alloc.deallocate(this->_data, this->_capacity);
				}
				this->_capacity = new_capacity;
				this->_data = new_data;
				position = iterator(&this->_data[i]);
			}
			// insert
			it = position;
			for (InputIterator range = first; range != last; range++)
			{
				this->_alloc.construct(&*it, *range);
				this->_size++;
				it++;
			}
			// copy after insert
			i = 0;
			for (it = position + range; it != this->end(); it++)
			{
				this->_alloc.construct(&*it, tmp[i]);
				i++;
			}
			// free
			for (i = 0; i < tmp_size; i++)
				this->_alloc.destroy(&tmp[i]);
			this->_alloc.deallocate(tmp, tmp_size);
		}

		//[5] erase
		// position
		iterator erase(iterator position)
		{
			size_type tmp_size = 0;
			size_type i;
			pointer tmp;

			if (position == (this->end() - 1))
			{
				this->pop_back();
				return position;
			}
			for (iterator it = position + 1; it != this->end(); it++)
				tmp_size++;
			tmp = this->_alloc.allocate(tmp_size);
			i = 0;
			for (iterator it = position + 1; it != this->end(); it++)
			{
				this->_alloc.construct(&tmp[i], *it);
				this->_alloc.destroy(&*it);
				i++;
			}
			// erase
			this->_alloc.destroy(&*position);
			this->_size--;
			// copy after insert
			i = 0;
			for (iterator it = position; it != this->end(); it++)
			{
				this->_alloc.construct(&*it, tmp[i]);
				i++;
			}
			// free
			for (i = 0; i < tmp_size; i++)
				this->_alloc.destroy(&tmp[i]);
			this->_alloc.deallocate(tmp, tmp_size);
			return position;
		}

		// range
		iterator erase(iterator first, iterator last)
		{
			size_type tmp_size = 0;
			size_type i;
			pointer tmp;

			for (iterator it = last; it != this->end(); it++)
				tmp_size++;
			tmp = this->_alloc.allocate(tmp_size);
			i = 0;
			for (iterator it = last; it != this->end(); it++)
			{
				this->_alloc.construct(&tmp[i], *it);
				this->_alloc.destroy(&*it);
				i++;
			}
			// erase
			for (iterator it = first; it != last; it++)
			{
				this->_alloc.destroy(&*it);
				this->_size--;
			}
			// copy after insert
			i = 0;
			for (iterator it = first; it != this->end(); it++)
			{
				this->_alloc.construct(&*it, tmp[i]);
				i++;
			}
			// free
			for (i = 0; i < tmp_size; i++)
				this->_alloc.destroy(&tmp[i]);
			this->_alloc.deallocate(tmp, tmp_size);
			return first;
		}

		void swap(vector &x)
		{
			pointer tmp_data = this->_data;
			size_type tmp_size = this->_size;
			size_type tmp_capacity = this->_capacity;

			this->_data = x._data;
			this->_size = x._size;
			this->_capacity = x._capacity;

			x._data = tmp_data;
			x._size = tmp_size;
			x._capacity = tmp_capacity;
		}

		void clear()
		{
			while (this->_size != 0)
			{
				this->_alloc.destroy(&this->_data[this->_size - 1]);
				this->_size--;
			}
		}

		/*
		** --------------------------------- Allocator ---------------------------------
		*/

		allocator_type get_allocator() const
		{
			return this->_alloc;
		}

		v
	};

	/*
	** --------------------------------- Non-member function overloads ---------------------------------
	*/

	template <class T, class Alloc>
	void swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
	{
		x.swap(y);
	}

	//!!!! 구현해야 함

	// template <class T, class Alloc>
	// bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);

	// template <class T, class Alloc>
	// bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);

	// template <class T, class Alloc>
	// bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);

	// template <class T, class Alloc>
	// bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);

	// template <class T, class Alloc>
	// bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);

	// template <class T, class Alloc>
	// bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);

	// template <class T, class Alloc = allocator<T>>
	// class vector; // generic template

}

#endif