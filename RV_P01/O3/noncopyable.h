#ifndef O3LIB_NONCOPYABLE_H
#define O3LIB_NONCOPYABLE_H
#include "common.h"

//! declares a class or struct as being non-copyable; to be placed in the private section of a class/struct
#define O3_DECLARE_NONCOPYABLE(classname) \
		classname(classname const &); \
		classname &operator=(classname const &)

#endif // O3LIB_NONCOPYABLE_H
