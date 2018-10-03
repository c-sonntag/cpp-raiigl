#pragma once

#include <raiigl/buffer.hpp>
#include <raiigl/gl430.hpp>

#include <GL/glew.h>

namespace raiigl {

  struct buffer_ssbo : public raiigl::buffer
  {
   public:
    buffer_ssbo( const buffer_usage _usage = buffer_usage::StaticDraw, const GLsizei _n = 1 ):
      buffer( buffer_type::ShaderStorage, std::move( _usage ), std::move( _n ) )
    { raiigl::gl430::check_compatibility(); }
   public:
    __forceinline void layout_binding( GLuint binding_num ) const
    { glBindBufferBase( GL_SHADER_STORAGE_BUFFER, std::move( binding_num ), id ); }
  };

}


