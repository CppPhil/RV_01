#ifndef O3LIB_CONTAINERS_H
#define O3LIB_CONTAINERS_H
#include "common.h"
#include "except.h"

//! define O3_NO_HASH_CONTAINERS to not have the unordered_map and unordered_set headers included
#ifndef O3_NO_HASH_CONTAINERS
#   include <unordered_map>
#   include <unordered_set>
#endif // O3_NO_HASH_CONTAINERS
#include <cstddef>
#include <iterator>
#include <utility>
#include <algorithm>

namespace o3 {
//! define O3_NO_HASH_CONTAINERS to not have the unordered_map and unordered_set headers included
#ifndef O3_NO_HASH_CONTAINERS
    using ::std::tr1::unordered_set;
    using ::std::tr1::unordered_multiset;
    using ::std::tr1::unordered_map;
    using ::std::tr1::unordered_multimap;
#endif // O3_NO_HASH_CONTAINERS
    
    //! much like C++11s std::array; see: http://en.cppreference.com/w/cpp/container/array
    template <typename Ty, std::size_t Num>
    class array {
    public:
        typedef Ty value_type;
        typedef value_type *iterator;
        typedef value_type const *const_iterator;
        typedef value_type &reference;
        typedef value_type const &const_reference;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
        
        iterator begin() {
            return elems;
        }
        
        const_iterator begin() const {
            return elems;
        };
        
        const_iterator cbegin() const {
            return elems;
        }
        
        iterator end() {
            return elems;
        }
        
        const_iterator end() const {
            return elems;
        }
        
        const_iterator cend() const {
            return elems;
        }
        
        reverse_iterator rbegin() {
            return reverse_iterator(end());
        }
        
        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(end());
        }
        
        const_reverse_iterator crbegin() const {
            return const_reverse_iterator(end());
        }
        
        reverse_iterator rend() {
            return reverse_iterator(begin());
        }
        
        const_reverse_iterator rend() const {
            return const_reverse_iterator(begin());
        }
        
        const_reverse_iterator crend() const {
            return const_reverse_iterator(begin());
        }
        
        reference operator[](size_type i) {
            return elems[i];
        }
        
        const_reference operator[](size_type i) const {
            return elems[i];
        }
        
        reference at(size_type i) {
            if (i >= Num) {
                throw bad_index("bad index in function: o3::array::at (non-const)");
            }
            return elems[i];
        }
        
        const_reference at(size_type i) const {
            if (i >= Num) {
                throw bad_index("bad index in function: o3::array::at (const)");
            }
            return elems[i];
        }
        
        reference front() {
            return elems[0];
        }
        
        const_reference front() const {
            return elems[0];
        }
        
        reference back() {
            return elems[Num - 1];
        }
        
        const_reference back() const {
            return elems[Num - 1];
        }
        
        static size_type size() {
            return Num;
        }
        
        static bool empty() {
            return false;
        }
        
        static size_type max_size() {
            return Num;
        }
        
        void swap(array<value_type, Num> &other) {
            for (size_type i = 0; i < Num; ++i) {
                std::swap(elems[i], other.elems[i]);
            }
        }
        
        value_type const *data() const {
            return elems;
        }
        
        value_type *data() {
            return elems;
        }
        
        //! returns a pointer with low level constness to the internal c-array
        value_type const *const_data() const {
            return elems;
        }
                
        template <typename Type>
        array &operator=(array<Type, Num> const &ary) {
            std::copy(ary.begin(), ary.end(), begin());
            return *this;
        }
        
        //! an alias for fill
        void assign(value_type const &v) {
            fill(v);
        }
        
        void fill(value_type const &v) {
            std::fill_n(begin(), size(), v);
        }
                
        //! the underlying c-array is publicly accessible for direct access
        value_type elems[Num];
    }; // END of class array
    
    template <typename Ty, std::size_t Num>
    bool operator==(array<Ty, Num> const &a, array<Ty, Num> const &b) {
        return std::equal(a.begin(), a.end(), b.begin());
    }
    
    template <typename Ty, std::size_t Num>
    bool operator<(array<Ty, Num> const &a, array<Ty, Num> const &b) {
        return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
    }
    
    template <typename Ty, std::size_t Num>
    bool operator!=(array<Ty, Num> const &a, array<Ty, Num> const &b) {
        return !(a == b);
    }
    
    template <typename Ty, std::size_t Num>
    bool operator>(array<Ty, Num> const &a, array<Ty, Num> const &b) {
        return b < a;
    }
    
    template <typename Ty, std::size_t Num>
    bool operator<=(array<Ty, Num> const &a, array<Ty, Num> const &b) {
        return !(b < a);
    }
    
    template <typename Ty, std::size_t Num>
    bool operator>=(array<Ty, Num> const &a, array<Ty, Num> const &b) {
        return !(a < b);
    }
    
    template <typename Ty, std::size_t Num>
    O3_FORCE_INLINE void swap(array<Ty, Num> &a, array<Ty, Num> &b) {
        a.swap(b);
    }
} // END of namespace o3

#endif // O3LIB_CONTAINERS_H
