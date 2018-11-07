#pragma once

#include <raiigl/classes/non_copyable.hpp>

#include <GL/glew.h>

#include <string>
#include <istream>

namespace raiigl {

  enum class shader_type : GLuint
  {
    Vertex   = GL_VERTEX_SHADER,
    Fragment = GL_FRAGMENT_SHADER,
    Compute  = GL_COMPUTE_SHADER
  };

  struct shader : public raiigl::classes::non_copyable
  {
   public:
    const shader_type type;
    const GLuint id;

   protected:
    bool destroyed = false;

   public:
    shader( const std::string & code, shader_type _type );

    __forceinline shader( std::istream & code, shader_type _type ) :
      shader( to_string( code ), std::move( _type ) )
    { }

    __forceinline ~shader() {
      if ( id > 0 ) glDeleteShader( id );
      destroyed = true;
    }

   public:
    __forceinline shader( shader && s ) :
      type( std::move( s.type ) ),
      id( std::move( s.id ) ),
      destroyed( std::move( s.destroyed ) )
    { const_cast<GLuint &>( s.id ) = 0; }

   private:
    static std::string to_string( std::istream & code );

  };

}

// Include ipp file
#include <raiigl/ipp/shader.ipp>


