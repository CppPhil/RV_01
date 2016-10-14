#ifndef MEDIAN_H
#define MEDIAN_H
#include <ltiImage.h>
#include "O3/macros.h"

namespace app {
    struct Mask {
        O3_FORCE_INLINE Mask(int x_, int y_)
            : x(x_), 
              y(y_) { }

        int x;
        int y;
    };

    struct Naive { };
    struct Fast { };

    template <typename Strategy>
    O3_FORCE_INLINE void median(lti::channel8 const &srcPic,
                                lti::channel8 &dstPic,
                                Mask mask,
                                Strategy strat = (Strategy())) {

        medianImpl(srcPic, dstPic, mask, strat); 
    }

    void medianImpl(lti::channel8 const &srcPic,
                    lti::channel8 &dstPic,
                    Mask mask,
                    Naive strat);

    void medianImpl(lti::channel8 const &srcPic,
                    lti::channel8 &dstPic,
                    Mask mask,
                    Fast strat);

} // END of namespace app
#endif // MEDIAN_H
