#include <iostream> // std::cin, std::cout
#include <limits> // std::numeric_limits
#include "utils.h"

#ifdef max
#   undef max
#endif // max

namespace app {
    void keepWindowOpen(std::string const &prompt) O3_NOEXCEPT {
        std::cout << prompt << '\n' << std::flush;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
} // END of namespace app