#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iostream>

namespace ft
{
	struct input_iterator_tag
	{
	};
	struct output_iterator_tag
	{
	};
	struct forward_iterator_tag : input_iterator_tag
	{
	};
	struct bidirectional_iterator_tag : forward_iterator_tag
	{
	};
	struct random_access_iterator_tag : bidirectional_iterator_tag
	{
	};

	template <
		class Category,				// iterator::iterator_category
		class T,					// iterator::value_type
		class Distance = ptrdiff_t, // iterator::difference_type
		class Pointer = T *,		// iterator::pointer
		class Reference = T &		// iterator::reference
		>
	class iterator
	{
		public:
			typedef T value_type;
			typedef Distance difference_type;
			typedef Pointer pointer;
			typedef Reference reference;
			typedef Category iterator_category;
	};

	template <class Iterator>
	class iterator_traits
	{
		public:
			typedef typename Iterator::iterator_category iterator_category;
			typedef typename Iterator::value_type value_type;
			typedef typename Iterator::difference_type difference_type;
			typedef typename Iterator::pointer pointer;
			typedef typename Iterator::reference reference;
	};

	template <class T>		   // = template <typename T>
	class iterator_traits<T *> // template 특수화
	{
		public:
			typedef random_access_iterator_tag iterator_category;
			typedef T value_type;
			typedef ptrdiff_t difference_type;
			typedef T *pointer;
			typedef T &reference;
	};

	template <class T>
	class iterator_traits<const T *>
	{
		public:
			typedef random_access_iterator_tag iterator_category;
			typedef T value_type;
			typedef ptrdiff_t difference_type;
			typedef T *pointer;
			typedef T &reference;
	};

} // namespace ft

#endif