#pragma once

#include <raiigl/classes/non_copyable_movable.hpp>

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

  struct shader
  {
   public:
    const shader_type type;

   public:
    const GLuint id;

   public:
    shader( const std::string & code, shader_type _type );

    __forceinline shader( std::istream & code, shader_type _type ) :
      shader( to_string( code ), std::move( _type ) )
    {}

    __forceinline ~shader()
    { glDeleteShader( id ); }

   private:
    raiigl_classes_non_copyable_movable( shader )

   private:
    static std::string to_string( std::istream & code );

  };

}

// Include ipp file
#include <raiigl/ipp/shader.ipp>


