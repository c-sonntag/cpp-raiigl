#pragma once

#include <bits/move.h>

#define raiigl_classes_non_copyable_movable(classname)  \
  classname( classname && ) = default;                  \
  classname( const classname & ) = delete;              \
  classname & operator=( const classname & ) = delete;


// /* Disable copy from lvalue. */
// /* Enable move.  */
//
