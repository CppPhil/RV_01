#include <algorithm>
#include "O3/memory.h"
#include "O3/containers.h"
#include "Median.h"

namespace app {
    void medianImpl(lti::channel8 const &srcPic,
                    lti::channel8 &dstPic,
                    Mask mask,
                    Naive strat) {
        static int const divisor = 2;

        if (mask.x < 1 || mask.y < 1) {
            throw std::logic_error(std::string("invalid mask in ") + __FUNCTION__);
        }

        int const xBegin = mask.x / divisor;
        int const yBegin = mask.y / divisor;
        int const xEnd = srcPic.columns() - xBegin;
        int const yEnd = srcPic.rows() - yBegin;

        int const maskSize = mask.x * mask.y;
        
        o3::scoped_array<int> curValues(new int[maskSize]());
        int const midIndex = maskSize / 2 + 1;
        int * const itBegin = curValues.get();
        int * const itEnd = curValues.get() + maskSize;

        for (int x = xBegin; x < xEnd; ++x) {
            for (int y = yBegin; y < yEnd; ++y) {
                int *it = itBegin;
                for (int i = x - xBegin; i <= x + xBegin; ++i) { // collect surrounding values
                    for (int j = y - yBegin; j <= y + yBegin; ++j) {
                        *it = srcPic[j][i];
                        ++it;
                    }
                }
                std::sort(itBegin, itEnd);
                dstPic[y][x] = curValues.get()[midIndex];
            }
        }        
    }

    O3_FORCE_INLINE int getTargetColor(lti::channel8 const &sPic,
                                       int const pointX, int const pointY,
                                       int const mx, int const my,
                                       int const med) {

        enum {
            maxGrayScaleValue = 256
        };
    
        int targetColor = -1;
        o3::array<int, maxGrayScaleValue> histogram = { 0 };
        for (int x = pointX - mx; x <= pointX + mx; ++x) {
            for (int y = pointY - my; y <= pointY + my; ++y) {
                ++histogram[sPic[y][x]];
            }
        }

        o3::array<int, maxGrayScaleValue> accuHistogram(histogram);
        for (int i = 1; i <= maxGrayScaleValue; ++i) {
            accuHistogram[i] += accuHistogram[i - 1];
            if (accuHistogram[i] >= med) {
                targetColor = i; // <- median
                break;
            }
        }
        return targetColor;
    }
    
    void medianImpl(lti::channel8 const &srcPic,
                    lti::channel8 &dstPic,
                    Mask mask,
                    Fast strat) {
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

        for (int y = yBegin; y < yEnd; ++y) {
            for (int x = xBegin; x < xEnd; ++x) {
                dstPic[y][x] = getTargetColor(srcPic, x, y, 
                                              xBegin, yBegin,
                                              midIndex);
            }
        }
    }

} // END of namespace app
