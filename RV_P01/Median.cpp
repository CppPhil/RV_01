#include <algorithm>
#include "O3/memory.h"
#include "O3/containers.h"
#include "O3/macros.h"
#include "utils.h"
#include "Median.h"

namespace app {
    void medianImpl(O3_IN lti::channel8 const &srcPic,
                    O3_OUT lti::channel8 &dstPic,
                    Mask mask,
                    Naive strat) { // 'naive' median implementation

        O3_UNUSED(strat);
        static int const divisor = 2;

        if (mask.x < 1 || mask.y < 1) { // masks smaller than 1 are not allowed
            throw std::logic_error(std::string("invalid mask in ") + __FUNCTION__);
        }

        // x position in the picture to begin at
        int const xBegin = mask.x / divisor;

        // y position in the picture to begin at
        int const yBegin = mask.y / divisor;

        // x position in the picture to end at
        int const xEnd = srcPic.columns() - xBegin;

        // y position in the picture to end at
        int const yEnd = srcPic.rows() - yBegin;

        // these xBegin, xEnd, yBegin and yEnd variables are used to avoid the border.
        // the border will just be left black.

        int const maskSize = mask.x * mask.y; // the total mask size of the median mask to be used.
        
        // an array of the current values
        o3::scoped_array<int> curValues(new int[maskSize]()); 

        // the middle of the curValues array; contains the value to write after having been sorted below
        int const midIndex = maskSize / 2 + 1; 
        int * const itBegin = curValues.get(); // begin iterator over curValues
        int * const itEnd = curValues.get() + maskSize; // end iterator over curValues

        for (int x = xBegin; x < xEnd; ++x) {
            for (int y = yBegin; y < yEnd; ++y) { // iterate over the image
                int *it = itBegin;
                for (int i = x - xBegin; i <= x + xBegin; ++i) { // collect surrounding values
                    for (int j = y - yBegin; j <= y + yBegin; ++j) {
                        *it = srcPic[j][i]; // write them to curValues using the iterator
                        ++it;
                    }
                }
                std::sort(itBegin, itEnd); // sort curValues

                // write the midIndex value to the destination image
                dstPic[y][x] = static_cast<lti::ubyte>(curValues[midIndex]); 
            }
        }        
    } // END medianImpl

    //! returns the color to write at pointY, pointX; used by histogram median
    O3_FORCE_INLINE int getTargetColor(O3_IN lti::channel8 const &sPic,
                                       int const pointY, int const pointX,
                                       int const my, int const mx,
                                       int const med) {

        typedef o3::array<int, MAX_GRAYSCALE + 1> Histogram;

        int targetColor = -1;
        Histogram histogram = { 0 };
        for (int x = pointX - mx; x <= pointX + mx; ++x) {
            for (int y = pointY - my; y <= pointY + my; ++y) {
                ++histogram[sPic[y][x]]; // count the occurences of the grayscale values in the picture
            }
        }

        Histogram accuHistogram(histogram); // copy the histogram
        for (int i = 1; i <= MAX_GRAYSCALE; ++i) {
            accuHistogram[i] += accuHistogram[i - 1]; // add the previous one
            if (accuHistogram[i] >= med) { // if there are enough values
                targetColor = i; // <- median
                break; // return the targetColor
            }
        }
        return targetColor;
    }
    
    void medianImpl(O3_IN lti::channel8 const &srcPic,
                    O3_OUT lti::channel8 &dstPic,
                    Mask mask,
                    Fast strat) { // fast median implementation

        O3_UNUSED(strat);
        static int const divisor = 2;

        if (mask.x < 1 || mask.y < 1) {
            throw std::logic_error(std::string("invalid mask in ") + __FUNCTION__);
        }

        int const xBegin = mask.x / divisor;
        int const yBegin = mask.y / divisor;
        int const xEnd = srcPic.columns() - xBegin;
        int const yEnd = srcPic.rows() - yBegin;

        int const maskSize = mask.x * mask.y;

        int const midIndex = maskSize / 2 + 1;

        for (int y = yBegin; y < yEnd; ++y) { // iterator over the image
            for (int x = xBegin; x < xEnd; ++x) {
                // write the values to the destination image.
                dstPic[y][x] = static_cast<lti::ubyte>(
                                   getTargetColor(srcPic, y, x, 
                                                  yBegin, xBegin,
                                                  midIndex));
            }
        }
    }
} // END of namespace app
