#ifndef O3LIB_ALGORITHM_H
#define O3LIB_ALGORITHM_H
#include "common.h"
#include <algorithm>
#include <utility>
#include <functional>
#include <cassert>

namespace o3 {
    using ::std::for_each;
    using ::std::count;
    using ::std::count_if;
    using ::std::mismatch;
    using ::std::equal;
    using ::std::find;
    using ::std::find_if;
    using ::std::find_end;
    using ::std::find_first_of;
    using ::std::adjacent_find;
    using ::std::search;
    using ::std::search_n;
    using ::std::copy;
    using ::std::copy_backward;
    using ::std::fill;
    using ::std::fill_n;
    using ::std::transform;
    using ::std::generate;
    using ::std::generate_n;
    using ::std::remove;
    using ::std::remove_if;
    using ::std::remove_copy;
    using ::std::remove_copy_if;
    using ::std::replace;
    using ::std::replace_if;
    using ::std::replace_copy;
    using ::std::replace_copy_if;
    using ::std::swap;
    using ::std::swap_ranges;
    using ::std::iter_swap;
    using ::std::reverse;
    using ::std::reverse_copy;
    using ::std::rotate;
    using ::std::rotate_copy;
    using ::std::unique;
    using ::std::unique_copy;
    using ::std::partition;
    using ::std::stable_partition;
    using ::std::sort;
    using ::std::partial_sort;
    using ::std::partial_sort_copy;
    using ::std::stable_sort;
    using ::std::nth_element;
    using ::std::lower_bound;
    using ::std::upper_bound;
    using ::std::binary_search;
    using ::std::equal_range;
    using ::std::merge;
    using ::std::inplace_merge;
    using ::std::includes;
    using ::std::set_difference;
    using ::std::set_intersection;
    using ::std::set_symmetric_difference;
    using ::std::set_union;
    using ::std::make_heap;
    using ::std::push_heap;
    using ::std::pop_heap;
    using ::std::sort_heap;
    using ::std::max;
    using ::std::max_element;
    using ::std::min;
    using ::std::min_element;
    using ::std::lexicographical_compare;
    using ::std::next_permutation;
    using ::std::prev_permutation;
    
    //! http://en.cppreference.com/w/cpp/algorithm/copy
    template <typename InpIt, typename OutIt, typename UnaryPredicate>
    OutIt copy_if(InpIt first, InpIt last, OutIt d_first, UnaryPredicate pred) {
        while (first != last) {
            if (pred(*first)) {
                *d_first++ = *first;
            }
            ++first;
        }
        return d_first;
    }
    
    //! http://en.cppreference.com/w/cpp/algorithm/copy_n
    template <typename InputIt, typename Size, typename OutputIt>
    OutputIt copy_n(InputIt first, Size count, OutputIt result) {
        if (count > 0) {
            *result++ = *first;
            for (Size i = 1; i < count; ++i) {
                *result++ = *++first;
            }
        }
        return result;
    }
    
    //! http://en.cppreference.com/w/cpp/algorithm/partition_copy
    template <typename InputIt, typename OutputIt1,
              typename OutputIt2, typename UnaryPredicate>
    std::pair<OutputIt1, OutputIt2> partition_copy(InputIt first, InputIt last,
                                                   OutputIt1 d_first_true, OutputIt2 d_first_false,
                                                   UnaryPredicate p) {
        while (first != last) {
            if (p(*first)) {
                *d_first_true = *first;
                ++d_first_true;
            } else {
                *d_first_false = *first;
                ++d_first_false;
            }
            ++first;
        }
        return std::pair<OutputIt1, OutputIt2>(d_first_true, d_first_false);
    }
    
    //! behaves like copy_if with a negated predicate
    template <typename OutIt, typename InpIt, typename UnaryPredicate>
    OutIt copy_if_not(InpIt begin, InpIt end, OutIt dest, UnaryPredicate p) {
        for (; begin != end; ++begin) {
            if (!p(*begin)) {
                *dest = *begin;
                ++dest;
            }
        }
    }
    
    //! aen.cppreference.com/w/cpp/algorithm/find
    template <typename Iter, typename UnaryPredicate>
    Iter find_if_not(Iter begin, Iter end, UnaryPredicate predicate) {
        for (; begin != end; ++begin) {
            if (!predicate(*begin)) {
                return begin;
            }
        }
        return end;
    }
    
    //! http://en.cppreference.com/w/cpp/algorithm/all_any_none_of
    template <typename Iter, typename UnaryPredicate>
    bool all_of(Iter begin, Iter end, UnaryPredicate pred) {
        return find_if_not(begin, end, pred) == end;
    }
    
    //! http://en.cppreference.com/w/cpp/algorithm/all_any_none_of
    template <typename Iter, typename UnaryPredicate>
    bool any_of(Iter begin, Iter end, UnaryPredicate pred) {
        return std::find_if(begin, end, pred) != end;
    }
    
    //! http://en.cppreference.com/w/cpp/algorithm/all_any_none_of
    template <typename InputIt, typename UnaryPredicate>
    bool none_of(InputIt first, InputIt last, UnaryPredicate p) {
        return std::find_if(first, last, p) == last;
    }
    
    //! http://en.cppreference.com/w/cpp/algorithm/iota
    template <typename ForwardIt, typename Ty>
    ForwardIt iota(ForwardIt first, ForwardIt last, Ty i0) {
        for (; first != last; ++first, ++i0) {
            *first = i0;
        }
        return first;
    }
    
    /*! slides the range in a container denoted by first and last to place in the same container.
        after the operation the range denoted by first and last will now begin at place.
        returns the new first and last iterators of the range that was slid within the container.
        Note that all iterators must point into the same container
        Also note the the last iterator is not considered part of the range as ranges are typically half open in C++.
    */
    template <typename RandomAccessIterator>
    std::pair<RandomAccessIterator, RandomAccessIterator> slide(RandomAccessIterator const &first,
                                                                RandomAccessIterator const &last,
                                                                RandomAccessIterator const &place) {
        if (place < first) {
            return std::make_pair(place, rotate(place, first, last));
        }
        
        if (last < place) {
            return std::make_pair(rotate(first, last, place), place);
        }
        
        return std::make_pair(first, last);
    }
    
    //! http://en.cppreference.com/w/cpp/algorithm/clamp
    template <typename Ty, typename Compare>
    Ty const &clamp(Ty const &v, Ty const &lo, Ty const &hi, Compare comp) {
        return assert(!comp(hi, lo)),
            comp(v, lo) ? lo : comp(hi, v) ? hi : v;
    }
    
    //! http://en.cppreference.com/w/cpp/algorithm/clamp
    template <typename Ty>
    Ty const &clamp(Ty const &v, Ty const &lo, Ty const &hi) {
        return clamp(v, lo, hi, (std::less<Ty>()));
    }
    
    //! functor returned by the push_back function
    template <typename Cont>
    class push_back_functor {
    public:
        typedef push_back_functor this_type;
        
        explicit push_back_functor(Cont &cont)
            : cont_(&cont) { }
        
        //! appends the element passed to the target container
        template <typename Ty>
        this_type &operator()(Ty const &ty) {
            cont_->push_back(ty);
            return *this;
        }
        
    private:
        Cont *cont_;
    }; // END of class push_back_functor
    
    //! functor returned by push_front function
    template <typename Cont>
    class push_front_functor {
    public:
        typedef push_front_functor this_type;
        
        explicit push_front_functor(Cont &cont)
            : cont_(&cont) { }
        
        //! prepends the element passed to the target container
        template <typename Ty>
        this_type &operator()(Ty const &ty) {
            cont_->push_front(ty);
            return *this;
        }
        
    private:
        Cont *cont_;
    }; // END of class push_front_functor
    
    //! functor returned by insert function
    template <typename Cont>
    class insert_functor {
    public:
        typedef insert_functor this_type;
        
        explicit insert_functor(Cont &cont)
            : cont_(&cont) { }
        
        //! inserts ty at the position denoted by it into the target container
        template <typename Iter, typename Ty>
        this_type &operator()(Iter it, Ty const &ty) {
            cont_->insert(it, ty);
            return *this;
        }
        
    private:
        Cont *cont_;
    }; // END of class insert_functor
    
    //! creates a push_back_functor which can be used to push elements to the back of the container passed in using the call operator.
    template <typename Cont>
    push_back_functor<Cont> push_back(Cont &cont) {
        return push_back_functor<Cont>(cont);
    }
    
    //! creates a push_front_functor which can be used to push elements to the front of the container passed in using the call operator.
    template <typename Cont>
    push_front_functor<Cont> push_front(Cont &cont) {
        return push_front_functor<Cont>(cont);
    }
    
    //! creates an insert_functor which can be used to insert elements into the container passed in at the position denoted by an iterator using the call operator.
    template <typename Cont>
    insert_functor<Cont> insert(Cont &cont) {
        return insert_functor<Cont>(cont);
    }
    
} // END of namespace o3

#endif // O3LIB_ALGORITHM_H
