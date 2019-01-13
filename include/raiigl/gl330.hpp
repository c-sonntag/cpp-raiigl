#pragma once

#include <raiigl/gl320.hpp>

namespace raiigl {

  struct gl330 : public gl320
  {
    static __forceinline void check_compatibility() { raiigl_glew_throw_check( GLEW_VERSION_3_3 ); }

    // ---- ----

    // ---- ----



  };

}

