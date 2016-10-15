#ifndef SOBEL_H
#define SOBEL_H
#include <cmath>
#include <ltiImage.h>
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

    namespace riparoo {
        O3_FORCE_INLINE int xGradient(lti::channel8 const &img, int x, int y) {
            return img[y - 1][x - 1] +
                   2 * img[y][x - 1] +
                   img[y + 1][x - 1] -
                   img[y - 1][x + 1] -
                   2 * img[y][x + 1] -
                   img[y + 1][x + 1];
        }

        O3_FORCE_INLINE int yGradient(lti::channel8 const &img, int x, int y) {
            return img[y - 1][x - 1] +
                   2 * img[y - 1][x] +
                   img[y - 1][x + 1] -
                   2 * img[y + 1][x] -
                   img[y + 1][x + 1];
        }

    }


} // END of namespace app

#endif // SOBEL_H