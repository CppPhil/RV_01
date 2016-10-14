#ifndef O3LIB_FUNCTIONAL_H
#define O3LIB_FUNCTIONAL_H
#include "common.h"
#include <functional>

namespace o3 {
    //! http://en.cppreference.com/w/cpp/utility/functional/bit_and
    template <typename Ty>
    struct bit_and {
        Ty operator()(Ty const &a, Ty const &b) const {
            return a & b;
        }
    };
    
    //! http://en.cppreference.com/w/cpp/utility/functional/bit_or
    template <typename Ty>
    struct bit_or {
        Ty operator()(Ty const &a, Ty const &b) const {
            return a | b;
        }
    };
    
    //! functor that applies the bit_xor operator (^) to a and b like so: a ^ b
    template <typename Ty>
    struct bit_xor {
        Ty operator()(Ty const &a, Ty const &b) const {
            return a ^ b;
        }
    };
} // END of namespace o3

#endif // O3LIB_FUNCTIONAL_H
