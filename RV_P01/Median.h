#ifndef MEDIAN_H
#define MEDIAN_H
#include <ltiImage.h> // lti::channel8, ...
#include "O3/macros.h" // O3_FORCE_INLINE, O3_NOEXCEPT, ...

namespace app {
    //! Mask struct for the median filter
    struct Mask {
        //! constructs a Mask from two integers
        O3_FORCE_INLINE Mask(int x_, int y_) O3_NOEXCEPT
            : x(x_), 
              y(y_) { }

        //! mask x size
        int x;

        //! mask y size
        int y;
    };

    //! type to represent the 'naive', slow implementation of the median filter
    struct Naive { };

    //! type te represent the fast histogram based implementation of the median filter
    struct Fast { };

    /*! wrapper function that delegates to the appropriate medianImpl function
    **  based on the strategy to be used,
    **  called by RvP01::Median 
    **/
    template <typename Strategy>
    O3_FORCE_INLINE void median(O3_IN lti::channel8 const &srcPic,
                                O3_OUT lti::channel8 &dstPic,
                                Mask mask,
                                Strategy strat = (Strategy())) {

        medianImpl(srcPic, dstPic, mask, strat); 
    }

    //! 'naive' implementation of the median filter
    void medianImpl(O3_IN lti::channel8 const &srcPic,
                    O3_OUT lti::channel8 &dstPic,
                    Mask mask,
                    Naive strat);

    /*! fast histogram based implementation of the median filter,
    **  approximately two times faster than the 'naive' implementation
    **/
    void medianImpl(O3_IN lti::channel8 const &srcPic,
                    O3_OUT lti::channel8 &dstPic,
                    Mask mask,
                    Fast strat);
} // END of namespace app

#endif // MEDIAN_H
