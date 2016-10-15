#ifndef RV_P01_H
#define RV_P01_H
#include <ltiImage.h> // lti::channel8, ...
#include "O3/macros.h" // O3_IN, O3_OUT, ...

namespace app {
    //! class to be instantiated in the main function, calling the call operator will effectively launch the application
    class RvP01 {
    public:
        //! the call operator, to be called in the main function, delegate the argc and argv parameters to this member function
        void operator()(int argc, O3_IN char **argv);

        /*! applies median filter to the sPic passed using
        **  the median mask size of MaskSizeX and MaskSizeY,
        **  writes the result to dPic 
        **/
        void Median(O3_IN lti::channel8 const &sPic,
                    O3_OUT lti::channel8 &dPic,
                    int const MaskSizeX,
                    int const MaskSizeY);

        /*! applies sobel filter to sPic passed,
        **  outputs the gradient picture to GradientPic
        **  and the direction picture to DirectionPic
        **/
        void Sobel(O3_IN lti::channel8 const &sPic,
                   O3_OUT lti::channel8 &GradientPic,
                   O3_OUT lti::channel8 &DirectionPic);
    }; // END of class RV02
} // END of namespace app

#endif // RV_P01_H
