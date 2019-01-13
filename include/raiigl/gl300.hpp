#pragma once

#include <raiigl/gl200.hpp>

namespace raiigl {

  struct gl300 : public gl200
  {
    static __forceinline void check_compatibility() { raiigl_glew_throw_check( GLEW_VERSION_3_0 ); }

    // ---- ----

  };

}

