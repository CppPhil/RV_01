#ifndef RV_P01_H
#define RV_P01_H
#include <ltiImage.h>

namespace app {
    class RvP01 {
    public:
        void operator()(int argc, char **argv);

        void Median(lti::channel8 const &sPic,
                    lti::channel8 &dPic,
                    int const MaskSizeX,
                    int const MaskSizeY);

        void Sobel(lti::channel8 const &sPic,
                   lti::channel8 &GradientPic,
                   lti::channel8 &DirectionPic);
    }; // END of class RV02
} // END of namespace app
#endif // RV_P01_H
