#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
	public:
		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;

		explicit stack(const container_type &ctnr = container_type()) : _c(ctnr) {}

		stack(const stack &other) : _c(other._c) {}

		stack &operator=(const stack &other)
		{
			if (this != &other)
				this->_c = other._c;
			return *this;
		}

		~stack() {}

		bool empty() const
		{
			return this->_c.empty();
		}

		size_type size() const
		{
			return this->_c.size();
		}

		value_type &top()
		{
			return this->_c.back();
		}

		const value_type &top() const
		{
			return this->_c.back();
		}

		void push(const value_type &val)
		{
			this->_c.push_back(val);
		}

		void pop()
		{
			this->_c.pop_back();
		}

	protected:
		container_type _c;

	private:
		//when define friend keyword, have to use different template parameters
		//C = Container
		template <class U, class C> 
		friend bool operator==(const stack<U, C> &lhs, const stack<U, C> &rhs);

		template <class U, class C>
		friend bool operator!=(const stack<U, C> &lhs, const stack<U, C> &rhs);

		template <class U, class C>
		friend bool operator<(const stack<U, C> &lhs, const stack<U, C> &rhs);

		template <class U, class C>
		friend bool operator<=(const stack<U, C> &lhs, const stack<U, C> &rhs);

		template <class U, class C>
		friend bool operator>(const stack<U, C> &lhs, const stack<U, C> &rhs);

		template <class U, class C>
		friend bool operator>=(const stack<U, C> &lhs, const stack<U, C> &rhs);
	};

	template <class T, class Container>
	bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs._c == rhs._c);
	}

	template <class T, class Container>
	bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs._c != rhs._c);
	}

	template <class T, class Container>
	bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs._c < rhs._c);
	}

	template <class T, class Container>
	bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs._c <= rhs._c);
	}

	template <class T, class Container>
	bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs._c > rhs._c);
	}

	template <class T, class Container>
	bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs._c >= rhs._c);
	}

}

#endif