#ifndef CLPARAMS_H
#define CLPARAMS_H
#include <string> // std::string
#include "O3/macros.h" // O3_IN, ...

namespace app {
    //! wrapping namespace to simulate C++11 scoped enums
    namespace Filter {
        //! enum for the different type of filters
        enum Filter {
            //! represents the median filter
            Median, 

            //! represents the sobel filter
            Sobel,

            //! used to indicate that the filter to use could not be determined from the command line parameters
            Error
        }; // END of enum Filter
    } // END of namespace Filter
    
    //! struct that represents what actions are to be taken
    struct Action {
        //! the filter to use on the image
        Filter::Filter filter;

        //! path to the image
        std::string file;

        //! mask x size for median filter
        int maskX;

        //! mask y size for median filter
        int maskY;
    }; // END of struct Action

    //! parses the command line parameters given and produces an appropriate Action struct
    Action parseClParams(int argc, O3_IN char **argv);
} // END of namespace app

#endif // CLPARAMS_H
