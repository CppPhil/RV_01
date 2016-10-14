#ifndef O3LIB_EXCEPT_H
#define O3LIB_EXCEPT_H
#include "common.h"
#include "macros.h"
#include <exception>
#include <stdexcept>
#include <string>

//! macro that can be used to generate exception types; specify the name of the exception class to create in identifier and specify the base class in base_class; the base class must feature a virtual destructor.
#define O3_DECLARE_EXCEPTION_TYPE(identifier, base_class) \
    class identifier \
        : public base_class { \
    public: \
        typedef identifier this_type; \
        typedef base_class base_type; \
        \
        explicit identifier(std::string const &what_arg) \
            : base_type(what_arg) { } \
        explicit identifier(char const *what_arg) \
            : base_type(what_arg) { } \
        \
        virtual char const *what() const O3_NOEXCEPT { \
            return base_type::what(); \
        } \
    }

namespace o3 {
    //! exception that may be thrown to indicate attempts to dereference a null pointer
    O3_DECLARE_EXCEPTION_TYPE(nullpointer_exception, std::logic_error);
    
    //! exception that represents an assertion violation
    O3_DECLARE_EXCEPTION_TYPE(assertion_violation, std::runtime_error);
    
    //! exception that represents a precondition violation
    O3_DECLARE_EXCEPTION_TYPE(precondition_violation, assertion_violation);
    
    //! exception that represents a post condition violation
    O3_DECLARE_EXCEPTION_TYPE(postcondition_violation, assertion_violation);
    
    //! exception that may be thrown to indicate attempts to access a range with a bad index; that is an index that would lead to out of bounds access
    O3_DECLARE_EXCEPTION_TYPE(bad_index, std::out_of_range);
} // END of namespace o3

#endif // O3LIB_EXCEPT_H
