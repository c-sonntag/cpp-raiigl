#pragma once

#include <raiigl/types.hpp>
#include <raiigl/gl_types.hpp>

#include <raiigl/classes/non_copyable.hpp>
#include <raiigl/classes/forceinline.hpp>

#include <GL/glew.h>

#include <bits/move.h>
#include <stdexcept>

namespace raiigl {

#define raiigl_glew_throw_check( v ) {if( !v ) throw std::runtime_error( "Current GLEW Instance not support: " # v ); }

  struct gl200 : public classes::non_copyable
  {
    static __forceinline void check_compatibility() { raiigl_glew_throw_check( GLEW_VERSION_2_0 ); }

    // ---- ----

    __forceinline void draw_arrays( const primitive_type mode, const uint first, const uint count ) const
    { glDrawArrays( static_cast<GLenum>( mode ), static_cast<GLsizei>( first ), static_cast<GLsizei>( count ) ); }

    __forceinline void draw_elements( const primitive_type mode, const uint count, const void* const indices = nullptr, const indice_type type = raiigl::indice_type::Uint ) const
    { glDrawElements( static_cast<GLenum>( mode ), static_cast<GLsizei>( count ), static_cast<GLenum>( type ), indices ); }

    // ---- ----



  };

}

