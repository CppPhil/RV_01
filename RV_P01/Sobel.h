#ifndef SOBEL_H
#define SOBEL_H
#include <cmath>
#include "O3/macros.h"
#include "O3/algorithm.h"
#include "utils.h"

namespace app {
    enum {
        SobelMaskX = 3,
        SobelMaskY = 3
    };
    
    O3_FORCE_INLINE int getG(double gx, double gy) O3_NOEXCEPT {
        static int const maxVal = 255;
        static int const minVal = 0;
        int v = std::sqrt(std::pow(gx, 2.0) + std::pow(gy, 2.0));
        v = o3::clamp(v, minVal, maxVal);        
        return v;
    }
} // END of namespace app

#endif // SOBEL_H