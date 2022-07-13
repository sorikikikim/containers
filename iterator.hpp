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
        class Category,             // iterator::iterator_category
        class T,                    // iterator::value_type
        class Distance = ptrdiff_t, // iterator::difference_type
        class Pointer = T *,        // iterator::pointer
        class Reference = T &       // iterator::reference
        >
    class iterator
    {
        typedef T value_type;
        typedef Distance difference_type;
        typedef Pointer pointer;
        typedef Reference reference;
        typedef Category iterator_category;
    };

    template <class Iterator>
    class iterator_traits
    {
        typedef typename Iterator::iterator_category iterator_category;
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::difference_type difference_type;
        typedef typename Iterator::pointer pointer;
        typedef typename Iterator::reference reference;
    };

    template <class T>         // = template <typename T>
    class iterator_traits<T *> // template 특수화
    {
        typedef random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference;
    };

    template <class T>
    class iterator_traits<const T *>
    {
        typedef random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference;
    };

    template <class Iterator>
    class reverse_iterator
    {
    public:
        typedef Iterator iterator_type;
        typedef iterator_traits<Iterator>::iterator_category iterator_category;
        typedef iterator_traits<Iterator>::value_type value_type;
        typedef iterator_traits<Iterator>::difference_type differnce_type;
        typedef iterator_traits<Iterator>::pointer pointer;
        typedef iterator_traits<Iterator>::reference reference;

    protected:
        iterator_type base_iter;

    public:
        reverse_iterator() : base_iter(){};
        explicit reverse_iterator(iteratior_type it) : base_iter(it){};
        template <class Iter>
        reverse_iterator(const reverse_iterator<Iter> &rev_it) : base_iter(rev_it.base()){};
        virtual ~reverse_iterator(){};

        iterator_type base()
        {
            return base_iter;
        }

        operator reverse_iterator<const Interator>() const
        {
            return this->base_iter;
        }

        //operator
        reference operator*() const
        {
            iterator_type tmp(base_iter);
            return *(--tmp);
        }

        pointer operator+(differnce_type n)
        {
            return reverse_iterator(base_iter - n);
        }

        reverse_iterator operator++()
        {
            --base_iter;
            return *this;
        }
        reverse_iterator operator++(int)
        {
            reverse_iterator tmp = *this;
            --base_iter;
            return tmp;
        }

        reverse_iterator operator+=(differnce_type n)
        {
            base_iter -= n;
            return *this;
        }

        pointer operator-(differnce_type n)
        {
            return reverse_iterator(base_iter + n);
        }

        reverse_iterator operator--()
        {
            ++base_iter;
            return *this;
        }
        reverse_iterator operator--(int)
        {
            reverse_iterator tmp = *this;
            ++base_iter;
            return tmp;
        }

        reverse_iterator operator-=(differnce_type n)
        {
            base_iter += n;
            return *this;
        }

        pointer operator->() const
        {
            return &(operator*());
        }

        reference operator[](differnce_type n)
        {
            return (base_iter[-n - 1]);
        }
    };

    //relational operators
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

} // namespace ft

#endif