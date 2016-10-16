#ifndef UTILS_H
#define UTILS_H
#include <string> // std::string
#include <cstddef> // std::size_t
#include <sstream> // std::ostringstream
#include <stdexcept> // std::logic_error
#include <ltiImage.h> // lti::channel8, ...
#include "O3/macros.h" // O3_IN, O3_NOEXCEPT, ...

//! minimun possible grayscale value: 0
#define MIN_GRAYSCALE     0

//! maximum possible grayscale value: 255
#define MAX_GRAYSCALE   255

namespace app {
    //! converts something to a string
    template <typename Ty>
    O3_FORCE_INLINE std::string toString(Ty const &ty) {
        std::ostringstream oss;
        oss << ty;
        if (!oss) {
            throw std::logic_error("failed to convert in toString");
        }
        return oss.str();
    }

    //! keeps the console window open, waiting for the user to hit enter, displaying the prompt passed into the parameter
    void keepWindowOpen(O3_IN std::string const &prompt = "Hit enter to exit") O3_NOEXCEPT;

    //! returns true if the value passed into the parameter is odd; false otherwise
    template <typename Numeric>
    O3_FORCE_INLINE bool isOdd(Numeric numeric) O3_NOEXCEPT {
        static unsigned const lsb = 1U; 

        return bool(numeric & lsb);
    }

    //! return true if the value passed into the parameter is even; false otherwise
    template <typename Numeric>
    O3_FORCE_INLINE bool isEven(Numeric numeric) O3_NOEXCEPT {
        return !isOdd(numeric);
    }

    /*! fixes a median mask parameter,
    **  by returning the value one larger than
    **  the value passed into the parameter if it is even;
    **  otherwise returns the value passed into the parameter. 
    **/
    O3_FORCE_INLINE int fixedMedianParam(int param) O3_NOEXCEPT {
        param = (isOdd(param) ? param : param + 1);
        return param;
    }

    //! functor that flushes cout in its call operator
    struct CoutFlusher {
        //! the CoutFlusher structs call operator; will flush cout when called.
        void operator()() const O3_NOEXCEPT;
    };

    //! resizes the image passed into toRisize to have rows rows and columns columns
    void resizeImage(O3_OUT lti::channel8 &toResize,
                     int rows, int columns);

    //! returns true if the value passed into the parameter is negative; false otherwise
    template <typename Numeric>
    O3_FORCE_INLINE bool isNegative(Numeric numeric) O3_NOEXCEPT {
        static Numeric zero = Numeric(0);
        return numeric < zero;
    }
} // END of namespace app

#endif // UTILS_H
