#ifndef O3LIB_COMPILER_DETECTION_H
#define O3LIB_COMPILER_DETECTION_H

//! preprocessor symbol to represent the clang compiler; O3_COMPILER will be defined to this if clang is being used
#define O3_COMPILER_CLANG   1

//! preprocessor symbol to represent the microsoft visual compiler; O3_COMPILER will be defined to this if msvc in being used
#define O3_COMPILER_MSVC    2

//! preprocessor symbol to represent the GNU compiler; O3_COMPILER will be defined to this if GCC is being used
#define O3_COMPILER_GCC     3

#if defined(__clang__)
#   define O3_COMPILER      O3_COMPILER_CLANG
#elif defined(_MSC_VER)
#   define O3_COMPILER      O3_COMPILER_MSVC
#elif defined(__GNUC__)
#   define O3_COMPILER      O3_COMPILER_GCC
#else
#   error "The compiler being used is not supported by O3Lib"
#endif

#endif // O3LIB_COMPILER_DETECTION_H
