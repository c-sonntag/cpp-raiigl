#pragma once


#include <raiigl/gl420.hpp>

#include <GL/glew.h>

namespace raiigl {


  struct gl430 : public gl420
  {
    static constexpr __forceinline void check_compatibility() { raiigl_glew_throw_check( GLEW_VERSION_4_3 ); }

    __forceinline void multidraw_arrays_indirect( const primitive_type mode, const draw_arrays_indirect_command * const indirect_command_array, const GLsizei drawcount, const GLsizei stride ) const
    { glMultiDrawArraysIndirect( static_cast<GLenum>( mode ), reinterpret_cast<const void *>( indirect_command_array ), drawcount, stride ); }

    // __forceinline void multidraw_element_indirect( const primitive_type mode, const GLint first, const GLsizei count ) const
    // { glDrawArrays( static_cast<GLenum>( mode ), first, count ); }
    // glMultiDrawArraysIndirect
    // void glMultiDrawElementsIndirect( GLenum mode, GLenum type, const void * indirect, GLsizei drawcount, GLsizei stride );
    // void glMultiDrawArraysIndirect( GLenum mode, const void * indirect, GLsizei drawcount, GLsizei stride );


  };

}

