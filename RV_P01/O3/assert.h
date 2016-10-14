#ifndef O3LIB_ASSERT_H
#define O3LIB_ASSERT_H
#include <string>
#include "common.h"
#include "except.h"
#include "macros.h"

//! assert macro; will throw assertion_violation if the condition is false.
#define O3_ASSERT(cond) O3_DETAIL_BEGIN_MACRO \
    if (!(cond)) { \
        throw o3::assertion_violation(std::string("O3: Assertion violation at ") + __FILE__ + ": " + O3_STRINGIFY(__LINE__)); \
    } O3_DETAIL_END_MACRO

//! checks a precondition; throws precondition_violation if the condition is false.
#define O3_CHECK_PRE(cond) O3_DETAIL_BEGIN_MACRO \
    if (!(cond)) { \
        throw o3::precondition_violation(std::string("O3: Precondition violation at ") + __FILE__ + ": " + O3_STRINGIFY(__LINE__)); \
    } O3_DETAIL_END_MACRO

//! checks a postcondition; throw postcondition_violation if the condition is false.
#define O3_CHECK_POST(cond) O3_DETAIL_BEGIN_MACRO \
    if (!(cond)) { \
        throw o3::postcondition_violation(std::string("O3: Postcondition violation at ") + __FILE__ + ": " + O3_STRINGIFY(__LINE__)); \
    } O3_DETAIL_END_MACRO

#endif // O3LIB_ASSERT_H
