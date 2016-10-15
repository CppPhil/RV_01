#include <sstream> // std::stringstream
#include "O3/macros.h" // O3_IN, ...
#include "utils.h" // app::Filter::Filter, ...
#include "ClParams.h"

namespace app {
    Action parseClParams(int argc, O3_IN char **argv) {
        /* if using sobel or median with default mask we have 3 parameters;
           1 for the filter, 1 for the image and 1 for the application itself */
        static int const cParam1 = 3;

        // if using median with a custom mask, we have 2 more command line parameters for xMask and yMask respectively.
        static int const cParam2 = 5;

        // index in argv to get the string of this application; unused
        static int const thisApplicationOffset = 0;
        O3_UNUSED(thisApplicationOffset);

        // index for the filter; must be -median or -sobel
        static int const filterOffset = 1;

        // index for the image file to use
        static int const fileOffset = 2;

        // index for a custom median x mask; if used
        static int const maskXOffset = 3;

        // index for a custom median y mask; if used
        static int const maskYOffset = 4;

        // default x and y median mask size; used if no custom median mask parameters are used.
        static int const defaultMedianMaskSize = 9;

        static std::string const medianStr("-median"); // median string
        static std::string const sobelStr("-sobel");   // sobel string

        // usage string is supposed to be printed on error.
        static std::string const usage("Usage:\n"
                                       "-median or -sobel "
                                       "filename\n"
                                       "Examples:\nRV_P01.exe -sobel lena.bmp\n"
                                       "RV_P01.exe -median auge.bmp 15 15");
        
        // construct the Action struct to be returned
        Action result = { Filter::Error,           // by default we don't know the filter to use; so that's an error for now
                          usage,                   /* the string is set to usage by default;
                                                      will be overwritten if we get an actual file */
                          defaultMedianMaskSize,   // by default use the defaultMedianMaskSize for mask x
                          defaultMedianMaskSize }; // by default use the defaultMedianMaskSize for mask y

        if (argc != cParam1 && argc != cParam2) { // if we have neither 3 nor 5 command line parameters; it's an error.
            return result; /* return with result;
                              result still contains Filtert::Error as well as the usage string to be printed */
        }
        
        if (medianStr == argv[filterOffset]) { // if the filter is median
            result.filter = Filter::Median; // use median
        } else if (sobelStr == argv[filterOffset]) { // if the filter is sobel
            result.filter = Filter::Sobel; // use sobel
        } else {
            return result; // otherwise return an Action struct indicating an error.
        }
    
        result.file = argv[fileOffset]; // get the file that contains the image to use from the command line parameters.

        if (argc == cParam2) { // if there are 5 command line parameters; get the median x and y mask if possible
            std::stringstream ss(argv[maskXOffset]); /// stringstream that starts of with the string in argv[maskXOffset]
            int v = 0; // value to write to
            ss >> v; // stream into the integer
            if (ss) { // on success
                result.maskX = v; // use the value as the maskX
            }

            ss.clear(); // clear the stringstream to start over
            ss << argv[maskYOffset]; // stream the string at argv[maskYOffset] into the stringstream
            ss >> v; // stream into v
            if (ss) { // on success
                result.maskY = v; // use the value as the maskY
            }

            /* if any of these conversions from string to integer using stringstream fail,
               it implicitly falls back to the default median mask size for that parameter
               since the values read are only written into the Action structure on success. */
        }

        return result; // return the result
    } // END of function Action parseClParams(int argc, O3_IN char **argv)
} // END of namespace app
