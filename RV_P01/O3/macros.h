#ifndef O3LIB_MACROS_H
#define O3LIB_MACROS_H
#include "common.h"

#if O3_COMPILER == O3_COMPILER_CLANG
#    define O3_FORCE_INLINE      __attribute__((always_inline))
#    define O3_SUGGEST_INLINE    inline
#    define O3_PROHIBIT_INLINE   __attribute__((noinline))
#    define O3_RESTRICT          __restrict__
#    if __has_feature(cxx_noexcept)
#        define O3_HAS_NOEXCEPT  1
#    else
#        define O3_HAS_NOEXCEPT  0
#    endif
#elif O3_COMPILER == O3_COMPILER_MSVC
#    define O3_FORCE_INLINE      __forceinline
#    define O3_SUGGEST_INLINE    inline
#    define O3_PROHIBIT_INLINE   __declspec(noinline)
#    define O3_RESTRICT          __restrict
#    if _MSC_FULL_VER >= 190023026
#        define O3_HAS_NOEXCEPT  1
#    else
#        define O3_HAS_NOEXCEPT  0
#    endif
#elif O3_COMPILER == O3_COMPILER_GCC
#    define O3_FORCE_INLINE      __attribute__((always_inline)) inline
#    define O3_SUGGEST_INLINE    inline
#    define O3_PROHIBIT_INLINE   __attribute__((noinline))
#    define O3_RESTRICT          __restrict__
#    if __GNUC__ * 10 + __GNUC_MINOR__ >= 46
#        define O3_HAS_NOEXCEPT  1
#    else
#        define O3_HAS_NOEXCEPT  0
#    endif
#endif

#if O3_HAS_NOEXCEPT
#    define O3_NOEXCEPT          noexcept
#else
#    define O3_NOEXCEPT          throw()
#endif

#undef O3_HAS_NOEXCEPT

#define O3_DETAIL_BEGIN_MACRO    do {
#define O3_DETAIL_END_MACRO      } while (false)

//! casts the argument to void; useful to suppress compiler warnings about unused parameters
#define O3_UNUSED(param)         (static_cast<void>((param)))

//! expands to an expression resulting in the maximum value of a and b
#define O3_MAX(a, b)             (((a) > (b)) ? (a) : (b))

//! expands to an expression resulting in the minimum value of a and b
#define O3_MIN(a, b)             (((a) < (b)) ? (a) : (b))
#define O3_DETAIL_STRINGIFY(x)   #x

//! turns the consecutive tokens passed into a c-string literal
#define O3_STRINGIFY(x)          O3_DETAIL_STRINGIFY(x)
#define O3_DETAIL_GLUE(a, b)     a##b

//! glues two tokens together as one
#define O3_GLUE(a, b)            O3_DETAIL_GLUE(a, b)

//! inside of a class this refers to the current object itself
#define O3_SELF                  (*this)

//! macro to annotate input pointer or reference parameters
#define O3_IN

//! macro to annotate output pointer or reference parameters
#define O3_OUT

//! macro to annotate pointer or reference parameters as being used for both input and output
#define O3_INOUT

//! macro to annotate a pointer parameter as being an optional input parameter; pass O3_NULLPTR to not have the function use the parameter
#define O3_IN_OPT

//! macro to annotate a pointer parameter as being an optional output parameter; pass O3_NULLPTR to not have the function use the parameter
#define O3_OUT_OPT

//! macro to annotate a pointer parameter as being an optionar input and output parameter; pass O3_NULLPTR to not have the function use the parameter
#define O3_INOUT_OPT

//! macro to annotate a pointer return type as not being a null pointer
#define O3_RET_NOTNULL

//! macro to annotate a function as returning a value that shall be checked at the callsite
#define O3_CHECKRETURN

#endif // O3LIB_MACROS_H
