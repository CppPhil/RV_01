#ifndef O3LIB_ITERATOR_H
#define O3LIB_ITERATOR_H
#include "common.h"
#include "macros.h"
#include <cstddef>
#include <iterator>

namespace o3 {
    template <typename Cont>
    O3_FORCE_INLINE typename Cont::iterator begin(Cont &cont) {
        return cont.begin();
    }
    
    template <typename Cont>
    O3_FORCE_INLINE typename Cont::const_iterator begin(Cont const &cont) {
        return cont.begin();
    }
    
    template <typename Cont>
    O3_FORCE_INLINE typename Cont::const_iterator cbegin(Cont const &cont) {
        return cont.begin();
    }
    
    template <typename Ty, std::size_t Num>
    O3_FORCE_INLINE Ty *begin(Ty (&arr)[Num]) O3_NOEXCEPT {
        return arr;
    };
    
    template <typename Ty, std::size_t Num>
    O3_FORCE_INLINE Ty const *begin(Ty const (&arr)[Num]) O3_NOEXCEPT {
        return arr;
    };
    
    template <typename Ty, std::size_t Num>
    O3_FORCE_INLINE Ty const *cbegin(Ty const (&arr)[Num]) O3_NOEXCEPT {
        return arr;
    };
    
    template <typename Cont>
    O3_FORCE_INLINE typename Cont::iterator end(Cont &cont) {
        return cont.end();
    }
    
    template <typename Cont>
    O3_FORCE_INLINE typename Cont::const_iterator end(Cont const &cont) {
        return cont.end();
    }
    
    template <typename Cont>
    O3_FORCE_INLINE typename Cont::const_iterator cend(Cont const &cont) {
        return cont.end();
    }
    
    template <typename Ty, std::size_t  Num>
    O3_FORCE_INLINE Ty *end(Ty (&arr)[Num]) O3_NOEXCEPT {
        return arr + Num;
    };
    
    template <typename Ty, std::size_t Num>
    O3_FORCE_INLINE Ty const *end(Ty const (&arr)[Num]) O3_NOEXCEPT {
        return arr + Num;
    };
    
    template <typename Ty, std::size_t Num>
    O3_FORCE_INLINE Ty const *cend(Ty const (&arr)[Num]) O3_NOEXCEPT {
        return arr + Num;
    };
    
    template <typename Cont>
    O3_FORCE_INLINE typename Cont::reverse_iterator rbegin(Cont &cont) {
        return cont.rbegin();
    }
    
    template <typename Cont>
    O3_FORCE_INLINE typename Cont::const_reverse_iterator rbegin(Cont const &cont) {
        return cont.rbegin();
    }
    
    template <typename Cont>
    O3_FORCE_INLINE typename Cont::const_reverse_iterator crbegin(Cont const &cont) {
        return cont.rbegin();
    }
    
    template <typename Cont>
    O3_FORCE_INLINE typename Cont::reverse_iterator rend(Cont &cont) {
        return cont.rend();
    }
    
    template <typename Cont>
    O3_FORCE_INLINE typename Cont::const_reverse_iterator rend(Cont const &cont) {
        return cont.rend();
    }
    
    template <typename Cont>
    O3_FORCE_INLINE typename Cont::const_reverse_iterator crend(Cont const &cont) {
        return cont.rend();
    }
    
    template <typename Ty, std::size_t Num>
    O3_FORCE_INLINE std::reverse_iterator<Ty *> rbegin(Ty (&arr)[Num]) {
        return std::reverse_iterator<Ty *>(arr + Num);
    };
    
    template <typename Ty, std::size_t Num>
    O3_FORCE_INLINE std::reverse_iterator<Ty const *>rbegin(Ty const (&arr)[Num]) {
        return std::reverse_iterator<Ty const *>(arr + Num);
    };
    
    template <typename Ty, std::size_t Num>
    O3_FORCE_INLINE std::reverse_iterator<Ty const *>crbegin(Ty const (&arr)[Num]) {
        return std::reverse_iterator<Ty const *>(arr + Num);
    };
    
    template <typename Ty, std::size_t Num>
    O3_FORCE_INLINE std::reverse_iterator<Ty *> rend(Ty (&arr)[Num]) {
        return std::reverse_iterator<Ty *>(arr);
    };
    
    template <typename Ty, std::size_t Num>
    O3_FORCE_INLINE std::reverse_iterator<Ty const *> rend(Ty const (&arr)[Num]) {
        return std::reverse_iterator<Ty const *>(arr);
    };
    
    template <typename Ty, std::size_t Num>
    O3_FORCE_INLINE std::reverse_iterator<Ty const *> crend(Ty const (&arr)[Num]) {
        return std::reverse_iterator<Ty const *>(arr);
    };
    
    template <typename ForwardIt>
    O3_SUGGEST_INLINE ForwardIt next(ForwardIt iter, typename std::iterator_traits<ForwardIt>::difference_type n = 1) {
        while (n-- > 0) {
            ++iter;
        }
        return iter;
    }
    
    template <typename ForwardIt>
    O3_SUGGEST_INLINE ForwardIt prev(ForwardIt iter, typename std::iterator_traits<ForwardIt>::difference_type n = 1) {
        std::advance(iter, -n);
        return iter;
    }
} // END of namespace o3

#define O3_BEGIN_END(arg)     o3::begin((arg)), o3::end((arg))
#define O3_CBEGIN_CEND(arg)   o3::cbegin((arg)), o3::cend((arg))
#define O3_RBEGIN_REND(arg)   o3::rbegin((arg)), o3::rend((arg))
#define O3_CRBEGIN_CREND(arg) o3::crbegin((arg)), o3::crend((arg))

#endif // O3LIB_ITERATOR_H
