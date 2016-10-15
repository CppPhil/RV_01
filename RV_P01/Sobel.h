#ifndef SOBEL_H
#define SOBEL_H
#include <ltiImage.h>

namespace app {
    //! implementation function of the sobel filter, called by RvP01::Sobel
    void sobelImpl(O3_IN lti::channel8 const &sPic,
                   O3_OUT lti::channel8 &gradientPic,
                   O3_OUT lti::channel8 &directionPic);
} // END of namespace app

#endif // SOBEL_H
