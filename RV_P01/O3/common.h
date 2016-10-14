#ifndef O3LIB_COMMON_H
#define O3LIB_COMMON_H

// include macros for compiler detection
#include "compiler_detection.h"

// include ciso646 so that standard C++ alternative operators are available even on MSVC
#include <ciso646>

namespace o3 {
    //! a signed byte-sized type
    typedef signed char byte;

    //! an unsigned byte-sized type
    typedef unsigned char ubyte;
} // END of namespace o3

#endif // O3LIB_COMMON_H
