#ifndef O3LIB_FINAL_ACT_H
#define O3LIB_FINAL_ACT_H
#include "noncopyable.h"
#include "common.h"
#include "macros.h"

namespace o3 {
    //! ad-hoc RAII wrapper that can be created from any callable; will call the callable in its destructor.
    template <typename Callable>
    class final_act {
    public:
        typedef final_act this_type;
        typedef Callable element_type;
        
        explicit final_act(element_type callable) O3_NOEXCEPT
            : callable_(callable) { }
        
        ~final_act() O3_NOEXCEPT {
            callable_();
        }
        
    private:
        O3_DECLARE_NONCOPYABLE(final_act);
        
        element_type callable_;
    };
} // END of namespace o3

#endif // O3LIB_FINAL_ACT_H
