#include <algorithm>
#include "O3/memory.h"
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
    
    void medianImpl(lti::channel8 const &srcPic,
                    lti::channel8 &dstPic,
                    Mask mask,
                    Fast strat) {

    }

} // END of namespace app
