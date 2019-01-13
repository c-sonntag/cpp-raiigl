#pragma once

#include <raiigl/gl310.hpp>

namespace raiigl {

  struct gl320 : public gl310
  {
    static __forceinline void check_compatibility() { raiigl_glew_throw_check( GLEW_VERSION_3_2 ); }

    // ---- ----

    __forceinline void draw_elements_base_vertex( const primitive_type mode, const uint count, const GLint base_vertex, void* const indices = nullptr, const indice_type type = raiigl::indice_type::Uint ) const
    { glDrawElementsBaseVertex( static_cast<GLenum>( mode ), static_cast<GLsizei>( count ), static_cast<GLenum>( type ), indices, base_vertex ); }

  };

}

