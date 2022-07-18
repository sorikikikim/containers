#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iostream>

namespace ft
{
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : input_iterator_tag {};
	struct bidirectional_iterator_tag : forward_iterator_tag {};
	struct random_access_iterator_tag : bidirectional_iterator_tag {};

	template <
		class Category,				// iterator::iterator_category
		class T,					// iterator::value_type
		class Distance = ptrdiff_t, // iterator::difference_type
		class Pointer = T *,		// iterator::pointer
		class Reference = T &		// iterator::reference
		>
	class iterator //컨테이너 요소에 접근
	{
		public:
			typedef T 			value_type;
			typedef Distance 	difference_type;
			typedef Pointer 	pointer;
			typedef Reference 	reference;
			typedef Category 	iterator_category;
	};

	template <class Iterator>
	class iterator_traits  //각 요소에 대하여 저장
	{
		public:
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
			typedef typename Iterator::iterator_category	iterator_category;
	};

	// template 특수화
	template <class T>
	class iterator_traits<T *> 
	{
		public:
			typedef T 							value_type;
			typedef ptrdiff_t 					difference_type;
			typedef T							*pointer;
			typedef T							&reference;
			typedef random_access_iterator_tag	iterator_category;
	};

	template <class T>
	class iterator_traits<const T *>
	{
		public:
			typedef T							value_type;	
			typedef ptrdiff_t					difference_type;
			typedef T							*pointer;
			typedef T							&reference;
			typedef random_access_iterator_tag	iterator_category;
	};

} // namespace ft

#endif