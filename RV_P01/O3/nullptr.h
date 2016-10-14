#ifndef O3LIB_NULLPTR_H
#define O3LIB_NULLPTR_H
#include "common.h"
#include <cstddef>

namespace o3 {
    //! null pointer class
    class nullptr_t {
    public:
        typedef nullptr_t this_type;
        
        nullptr_t()
            : padding_(0) { }
    
        //! implicitly convertible to null pointer of any type
        template <typename Ty>
        operator Ty *() const {
            return 0;
        }
        
        //! implicitly convertible to null pointer of any member function pointer type
        template <typename Class, typename Ty>
        operator Ty Class:: *() const {
            return 0;
        }
        
        //! boolean evaluations will yield false
        operator void *() const {
            return 0;
        }
        
        friend bool operator==(this_type const &,
                               this_type const &) {
            return true;
        }
        
        friend bool operator!=(this_type const &,
                               this_type const &) {
            return false;
        }
        
    private:
        //! have the same size as a pointer
        void *padding_;
    }; // END of class nullptr_t
} // END of namespace o3

//! null pointer literal; yields a prvalue expression of type o3::nullptr_t
#define O3_NULLPTR  ((o3::nullptr_t()))

#endif // O3LIB_NULLPTR_H
