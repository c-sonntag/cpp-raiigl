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
    Compute  = GL_COMPUTE_SHADER,
    Geometry = GL_GEOMETRY_SHADER,
    Unknown = 0
  };

  std::string name( const shader_type& st );

  // ---- ----

  struct shader : public raiigl::classes::non_copyable
  {
   public:
    const shader_type type;
    const GLuint id;

   protected:
    bool invalid_state = false;

   public:
    shader( const std::string& code, shader_type _type );

    __forceinline shader( std::istream& code, shader_type _type ) :
      shader( to_string( code ), std::move( _type ) )
    { }

    __forceinline ~shader()
    {
      if( ( id > 0 ) && !invalid_state )
        glDeleteShader( id );
      invalid_state = true;
    }

   public:
    __forceinline shader( shader&& s ) :
      type( std::move( s.type ) ),
      id( std::move( s.id ) ),
      invalid_state( std::move( s.invalid_state ) )
    { const_cast<GLuint&>( s.id ) = 0; s.invalid_state = true; }

   private:
    static std::string to_string( std::istream& code );

  };

}

// Include ipp file
#include <raiigl/ipp/shader.ipp>


