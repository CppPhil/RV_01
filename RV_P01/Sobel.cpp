#ifndef _USE_MATH_DEFINES
#   define _USE_MATH_DEFINES
#endif
#include <cmath> // std::pow, std::atan2
#include "O3/macros.h" // O3_FORCE_INLINE, O3_IN, O3_OUT
#include "O3/algorithm.h" // o3::clamp
#include "utils.h" // MIN_GRAYSCALE, MAX_GRAYSCALE, isNegative
#include "Sobel.h"

namespace app {
    static long double const pi = 
#ifdef M_PI
        static_cast<long double>(M_PI);
#else
        3.14159265358979323846L;
#endif

    //! calculates the square of the value passed into the parameter and returns the result.
    O3_FORCE_INLINE double square(double val) {
        return std::pow(val, 2.0);
    }

    /*! returns Gx for the pixel at position y, x in the image img
    **  uses the following filter mask:
    **  |--------|
    **  |-1  0  1|
    **  |-2  0  2|
    **  |-1  0  1|
    **  |________|
    **/
    O3_FORCE_INLINE int getGx(O3_IN lti::channel8 const &img, int y, int x) {
        return img[y + 1][x + 1] +  // bottom right position in the filter mask
               2 * img[y][x + 1] +  // center right position in the filter mask
               img[y - 1][x + 1] -  // top right position in the filter mask
               img[y + 1][x - 1] -  // bottom left position in the filter mask
               2 * img[y][x - 1] -  // center left position in the filter mask
               img[y - 1][x - 1];   // top left position in the filter mask
    }

    /*! return Gy for the pixel at position y, x in the image img
    **  uses the following filter mask:
    **  |--------|
    **  |-1 -2 -1|
    **  | 0  0  0|
    **  | 1  2  1|
    **  |________|
    **/
    O3_FORCE_INLINE int getGy(O3_IN lti::channel8 const &img, int y, int x) {
        return img[y + 1][x - 1] + // bottom left position in the filter mask
               2 * img[y + 1][x] + // bottom center position in the filter mask
               img[y + 1][x + 1] - // bottom right position in the filter mask
               img[y - 1][x - 1] - // top left position in the filter mask
               2 * img[y - 1][x] - // top center position in the filter mask
               img[y - 1][x + 1];  // top right position in the filter mask
    }

    //! returns val + 360 if val is negative; val otherwise
    O3_FORCE_INLINE long double fixForAtan2(long double val) {
        static long double addThis = 360.0L;
        if (isNegative(val)) {
            return val + addThis;
        }
        return val;
    }

    void sobelImpl(O3_IN lti::channel8 const &sPic, // the source image 
                   O3_OUT lti::channel8 &gradientPic, // the gradient output image
                   O3_OUT lti::channel8 &directionPic) { // the direction output image

        static long double const directionMultiplier = 180.0L / pi;

        int const rows = sPic.rows(); // get the rows
        int const columns = sPic.columns(); // get the columns
                   
        int gx = 0; // gx starts out as 0
        int gy = 0; // gy starts out as 0

        for (int y = 1; y < rows - 1; ++y) {
            for (int x = 1; x < columns - 1; ++x) { // iterate over the source image, avoiding the border
                gx = getGx(sPic, y, x); // get the Gx for the current pixel
                gy = getGy(sPic, y, x); // get the Gy for the current pixel

                // write G to the gradientPic; G = sqrt(gx^2 + gy^2)
                gradientPic[y][x] = static_cast<lti::ubyte>(
                                        o3::clamp(static_cast<int>(std::sqrt(square(gx) + square(gy))),
                                                  MIN_GRAYSCALE,
                                                  MAX_GRAYSCALE));

                // write alpha to the directionPic; alpha = arctan(gy / gx) 
                directionPic[y][x] = static_cast<lti::ubyte>(
                                         std::atan2(fixForAtan2(gy),
                                                    fixForAtan2(gx)) * directionMultiplier
                                     );
            }
        }
    } // END of function sobelImpl
} // END of namespace app
