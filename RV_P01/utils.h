#ifndef UTILS_H
#define UTILS_H
#include <string> // std::string
#include "O3/macros.h"

namespace app {
    void keepWindowOpen(std::string const &prompt = "Hit any key to exit") O3_NOEXCEPT;

    template <typename Numeric>
    O3_FORCE_INLINE bool isOdd(Numeric numeric) O3_NOEXCEPT {
        static unsigned const lsb = 1U; 

        return bool(numeric & lsb);
    }

    template <typename Numeric>
    O3_FORCE_INLINE bool isEven(Numeric numeric) O3_NOEXCEPT {
        return !isOdd(numeric);
    }

    O3_FORCE_INLINE int fixedMedianParam(int param) O3_NOEXCEPT {
        param = (isOdd(param) ? param : param + 1);
        return param;
    }

} // END of namespace app

#endif // UTILS_H
