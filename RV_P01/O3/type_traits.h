#ifndef O3LIB_TYPE_TRAITS_H
#define O3LIB_TYPE_TRAITS_H
#include "common.h"
#include "macros.h"
#include "nullptr.h"
#include <cstddef>

namespace o3 {
    //! http://en.cppreference.com/w/cpp/types/integral_constant
    template <typename Ty, Ty v>
    struct integral_constant {
        static const Ty value = v;
        
        typedef Ty value_type;
        typedef integral_constant type;
        
        operator value_type() const O3_NOEXCEPT {
            return value;
        }
        
        value_type operator()() const O3_NOEXCEPT {
            return value;
        }
    };
    
    typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;
        
    //! http://en.cppreference.com/w/cpp/types/add_cv
    template <typename Ty>
    struct add_const {
        typedef const Ty type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/add_cv
    template <typename Ty>
    struct add_volatile {
        typedef volatile Ty type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/add_cv
    template <typename Ty>
    struct add_cv {
        typedef const volatile Ty type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/add_reference
    template <typename Ty>
    struct add_lvalue_reference {
        typedef Ty &type;
    };
    
    //! same as add_lvalue_reference
    template <typename Ty>
    struct add_reference {
        typedef typename add_lvalue_reference<Ty>::type type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/remove_reference
    template <typename Ty>
    struct remove_reference {
        typedef Ty type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/remove_reference
    template <typename Ty>
    struct remove_reference<Ty &> {
        typedef Ty type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/add_pointer
    template <typename Ty>
    struct add_pointer {
        typedef typename remove_reference<Ty>::type *type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/remove_cv
    template <typename Ty>
    struct remove_const {
        typedef Ty type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/remove_cv
    template <typename Ty>
    struct remove_const<const Ty> {
        typedef Ty type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/remove_cv
    template <typename Ty>
    struct remove_volatile {
        typedef Ty type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/remove_cv
    template <typename Ty>
    struct remove_volatile<volatile Ty> {
        typedef Ty type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/remove_cv
    template <typename Ty>
    struct remove_cv {
        typedef typename remove_volatile<typename remove_const<Ty>::type>::type type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/remove_extent
    template <typename Ty>
    struct remove_extent {
        typedef Ty type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/remove_extent
    template <typename Ty, std::size_t Ix>
    struct remove_extent<Ty[Ix]> {
        typedef Ty type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/remove_extent
    template <typename Ty>
    struct remove_extent<Ty[]> {
        typedef Ty type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/remove_all_extents
    template <typename Ty>
    struct remove_all_extents {
        typedef Ty type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/remove_all_extents
    template <typename Ty, std::size_t Ix>
    struct remove_all_extents<Ty[Ix]> {
        typedef typename remove_all_extents<Ty>::type type;
    };

    //! http://en.cppreference.com/w/cpp/types/remove_all_extents
    template <typename Ty>
    struct remove_all_extents<Ty[]> {
        typedef typename remove_all_extents<Ty>::type type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/remove_pointer
    template <typename Ty>
    struct remove_pointer {
        typedef Ty type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/remove_pointer
    template <typename Ty>
    struct remove_pointer<Ty *> {
        typedef Ty type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/remove_pointer
    template <typename Ty>
    struct remove_pointer<Ty * const> {
        typedef Ty type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/remove_pointer
    template <typename Ty>
    struct remove_pointer<Ty * volatile> {
        typedef Ty type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/remove_pointer
    template <typename Ty>
    struct remove_pointer<Ty * const volatile> {
        typedef Ty type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/is_same
    template <typename Ty1, typename Ty2>
    struct is_same : false_type { };
    
    //! http://en.cppreference.com/w/cpp/types/is_same
    template <typename Ty1>
    struct is_same<Ty1, Ty1> : true_type { };
    
    //! http://en.cppreference.com/w/cpp/types/is_array
    template <typename Ty>
    struct is_array : false_type { };
    
    //! http://en.cppreference.com/w/cpp/types/is_array
    template <typename Ty, std::size_t Nx>
    struct is_array<Ty[Nx]> : true_type { };
    
    //! http://en.cppreference.com/w/cpp/types/is_lvalue_reference
    template <typename Ty>
    struct is_lvalue_reference : false_type { };
    
    //! http://en.cppreference.com/w/cpp/types/is_lvalue_reference
    template <typename Ty>
    struct is_lvalue_reference<Ty &> : true_type { };
    
    //! http://en.cppreference.com/w/cpp/types/is_reference
    template <typename Ty>
    struct is_reference : is_lvalue_reference<Ty> { };
    
    //! http://en.cppreference.com/w/cpp/types/is_const
    template <typename Ty>
    struct is_const : false_type { };
    
    //! http://en.cppreference.com/w/cpp/types/is_const
    template <typename Ty>
    struct is_const<const Ty> : true_type { };
    
    //! http://en.cppreference.com/w/cpp/types/is_volatile
    template <typename Ty>
    struct is_volatile : false_type { };
    
    //! http://en.cppreference.com/w/cpp/types/is_volatile
    template <typename Ty>
    struct is_volatile<volatile Ty> : true_type { };
    
    //! http://en.cppreference.com/w/cpp/types/is_void
    template <typename Ty>
    struct is_void : is_same<void, typename remove_cv<Ty>::type> { };
    
    //! http://en.cppreference.com/w/cpp/types/is_null_pointer
    template <typename Ty>
    struct is_null_pointer : is_same<nullptr_t, typename remove_cv<Ty>::type>{ };
    
    //! http://en.cppreference.com/w/cpp/types/is_integral
    template <typename Ty>
    struct is_integral
        : integral_constant<bool,
                is_same<bool, typename remove_cv<Ty>::type>::value ||
                is_same<char, typename remove_cv<Ty>::type>::value ||
                is_same<signed char, typename remove_cv<Ty>::type>::value ||
                is_same<unsigned char, typename remove_cv<Ty>::type>::value ||
                is_same<wchar_t, typename remove_cv<Ty>::type>::value ||
                is_same<short, typename remove_cv<Ty>::type>::value ||
                is_same<unsigned short, typename remove_cv<Ty>::type>::value ||
                is_same<int, typename remove_cv<Ty>::type>::value ||
                is_same<unsigned, typename remove_cv<Ty>::type>::value ||
                is_same<long, typename remove_cv<Ty>::type>::value ||
                is_same<unsigned long, typename remove_cv<Ty>::type>::value ||
                is_same<long long, typename remove_cv<Ty>::type>::value ||
                is_same<unsigned long long, typename remove_cv<Ty>::type>::value> { };
        
    //! http://en.cppreference.com/w/cpp/types/is_floating_point
    template <typename Ty>
    struct is_floating_point
        : integral_constant<bool,
                is_same<float, typename remove_cv<Ty>::type>::value ||
                is_same<double, typename remove_cv<Ty>::type>::value ||
                is_same<long double, typename remove_cv<Ty>::type>::value> { };
    
    //! http://en.cppreference.com/w/cpp/types/is_arithmetic
    template <typename Ty>
    struct is_arithmetic
        : integral_constant<bool,
                is_integral<Ty>::value ||
                is_floating_point<Ty>::value> { };
    
    //! http://en.cppreference.com/w/cpp/types/is_fundamental
    template <typename Ty>
    struct is_fundamental
        : integral_constant<bool,
                is_arithmetic<Ty>::value ||
                is_void<Ty>::value ||
                is_null_pointer<Ty>::value> { };
    
    //! http://en.cppreference.com/w/cpp/types/is_compound
    template <typename Ty>
    struct is_compound
        : integral_constant<bool, !is_fundamental<Ty>::value> { };
    
    namespace detail {
        //! return type is 1 byte large if pointer to member function is a valid type for type Ty
        template <typename Ty>
        char is_class_helper(int Ty:: *);
        
        //! type that is guaranteed to be two bytes large
        struct two_bytes {
            char buf[2];
        };
        
        //! if and only if the member function pointer overload SFINAEs away this overload will be chosen.
        template <typename Ty>
        two_bytes is_class_helper(...);
        
        template <typename Ty>
        struct is_member_pointer_helper : false_type { };
        
        template <typename Ty, typename Ty2>
        struct is_member_pointer_helper<Ty Ty2:: *> : true_type { };
        
        template <typename Ty>
        struct is_pointer_helper : false_type { };
        
        template <typename Ty>
        struct is_pointer_helper<Ty *> : true_type { };
   
        template <typename Ty,
                  bool = is_arithmetic<Ty>::value>
        struct is_signed_helper
            : integral_constant<bool,
                    Ty(-1) < Ty(0)> { };
        
        template <typename Ty>
        struct is_signed_helper<Ty, false> : false_type { };
    
        template <typename Ty,
                  bool = is_arithmetic<Ty>::value>
        struct is_unsigned_helper
            : integral_constant<bool,
                    Ty(0) < Ty(-1)> { };
        
        template <typename Ty>
        struct is_unsigned_helper<Ty, false> : false_type { };
    } // END of namespace detail
   
    //! http://en.cppreference.com/w/cpp/types/is_unsigned
    template <typename Ty>
    struct is_unsigned
        : detail::is_unsigned_helper<Ty>::type { };
    
    //! http://en.cppreference.com/w/cpp/types/is_signed
    template <typename Ty>
    struct is_signed
        : detail::is_signed_helper<Ty>::type { };
    
    //! http://en.cppreference.com/w/cpp/types/is_pointer
    template <typename Ty>
    struct is_pointer : detail::is_pointer_helper<typename remove_cv<Ty>::type> { };
    
    //! http://en.cppreference.com/w/cpp/types/is_class
    template <typename Ty>
    struct is_class : integral_constant<bool,
            sizeof(detail::is_class_helper<Ty>(O3_NULLPTR)) == 1>{ };
    
    //! http://en.cppreference.com/w/cpp/types/is_member_pointer
    template <typename Ty>
    struct is_member_pointer
        : detail::is_member_pointer_helper<typename remove_cv<Ty>::type> { };
    
    //! http://en.cppreference.com/w/cpp/types/rank
    template <typename Ty>
    struct rank : integral_constant<std::size_t, 0> { };
    
    //! http://en.cppreference.com/w/cpp/types/rank
    template <typename Ty, std::size_t Ix>
    struct rank<Ty[Ix]> : integral_constant<std::size_t, rank<Ty>::value + 1> { };
    
    //! http://en.cppreference.com/w/cpp/types/rank
    template <typename Ty>
    struct rank<Ty[]> : integral_constant<std::size_t, rank<Ty>::value +1 > { };
    
    //! http://en.cppreference.com/w/cpp/types/enable_if
    template <bool Bool, typename Ty = void>
    struct enable_if { };
    
    //! http://en.cppreference.com/w/cpp/types/enable_if
    template <typename Ty>
    struct enable_if<true, Ty> {
        typedef Ty type;
    };
    
    //! opposite of enable_if; can be used to SFINAE a function overload away if the condition is true.
    template <bool Bool, typename Ty = void>
    struct disable_if {
        typedef Ty type;
    };
    
    //! //! opposite of enable_if; can be used to SFINAE a function overload away if the condition is true.
    template <typename Ty>
    struct disable_if<true, Ty> { };
    
    //! http://en.cppreference.com/w/cpp/types/conditional
    template <bool Bool, typename True, typename False>
    struct conditional {
        typedef True type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/conditional
    template <typename True, typename False>
    struct conditional<false, True, False> {
        typedef False type;
    };
    
    //! defines a dependent type type that is of the same type as the type in the template type parameter
    template <typename Ty>
    struct identity {
        typedef Ty type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/make_signed
    template <typename Ty>
    struct make_signed;
    
    //! http://en.cppreference.com/w/cpp/types/make_signed
    template <>
    struct make_signed<signed char> {
        typedef signed char type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/make_signed
    template <>
    struct make_signed<unsigned char> {
        typedef signed char type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/make_signed
    template <>
    struct make_signed<char> {
        typedef signed char type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/make_signed
    template <>
    struct make_signed<short> {
        typedef short type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/make_signed
    template <>
    struct make_signed<unsigned short> {
        typedef short type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/make_signed
    template <>
    struct make_signed<int> {
        typedef int type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/make_signed
    template <>
    struct make_signed<unsigned> {
        typedef int type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/make_signed
    template <>
    struct make_signed<long> {
        typedef long type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/make_signed
    template <>
    struct make_signed<unsigned long> {
        typedef long type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/make_signed
    template <>
    struct make_signed<long long> {
        typedef long long type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/make_signed
    template <>
    struct make_signed<unsigned long long> {
        typedef long long type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/make_unsigned
    template <typename Ty>
    struct make_unsigned;
    
    //! http://en.cppreference.com/w/cpp/types/make_unsigned
    template <>
    struct make_unsigned<char> {
        typedef unsigned char type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/make_unsigned
    template <>
    struct make_unsigned<signed char> {
        typedef unsigned char type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/make_unsigned
    template <>
    struct make_unsigned<unsigned char> {
        typedef unsigned char type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/make_unsigned
    template <>
    struct make_unsigned<short> {
        typedef unsigned short type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/make_unsigned
    template <>
    struct make_unsigned<unsigned short> {
        typedef unsigned short type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/make_unsigned
    template <>
    struct make_unsigned<int> {
        typedef unsigned type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/make_unsigned
    template <>
    struct make_unsigned<unsigned> {
        typedef unsigned type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/make_unsigned
    template <>
    struct make_unsigned<long> {
        typedef unsigned long type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/make_unsigned
    template <>
    struct make_unsigned<unsigned long> {
        typedef unsigned long type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/make_unsigned
    template <>
    struct make_unsigned<long long> {
        typedef unsigned long long type;
    };
    
    //! http://en.cppreference.com/w/cpp/types/make_unsigned
    template <>
    struct make_unsigned<unsigned long long> {
        typedef unsigned long long type;
    };
} // END of namespace o3

#endif // O3LIB_TYPE_TRAITS_H
