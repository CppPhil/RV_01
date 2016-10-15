#include <iostream> // std::cin, std::cout
#include <limits> // std::numeric_limits
#include "utils.h"

#ifdef max
#   undef max /* get rid of microsoft's max macro, as it will cause trouble */
#endif // max

namespace app {
    void keepWindowOpen(O3_IN std::string const &prompt) O3_NOEXCEPT {
        std::cout << prompt << '\n' << std::flush; // write the prompt to std::cout

        // ignore up to std::numeric_limits<std::streamsize>::max() characters until '\n'
        // this will effectively ignore characters until enter is hit.
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    void CoutFlusher::operator()() const O3_NOEXCEPT {
        std::cout << std::flush; // flush std::cout
    }

    void resizeImage(O3_OUT lti::channel8 &toResize, int rows, int columns) {
        static lti::ubyte const initialValue = 0U; // have the image start out with all black pixels
        static bool const copyData = false; // do not copy the data
        static bool const initNew = true; // initNew = true

        // resize the image that is to be resized so that it has as many rows and columns as it should have.
        toResize.resize(rows, columns, 
                        initialValue,
                        copyData, initNew);
    } // END of function void resizeImage(O3_OUT lti::channel8 &toResize, int rows, int columns)
} // END of namespace app

// redefine microsoft's max macro just in case
#define max(a,b)            (((a) > (b)) ? (a) : (b))
