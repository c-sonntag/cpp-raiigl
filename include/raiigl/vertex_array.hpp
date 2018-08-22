#pragma once

#include <raiigl/classes/non_copyable.hpp>

#include <GL/glew.h>

namespace raiigl {

  struct vertex_array : public classes::non_copyable
  {
   public:
    const GLsizei n;
    const GLuint id;

   private:
    __forceinline GLuint gen_vertex_array( GLsizei n )  {
      GLuint id;
      glGenVertexArrays( n, &id );
      return id;
    }

   public:
    vertex_array( GLsizei _n = 1 ) :
      n( std::move( _n ) ),
      id( gen_vertex_array( n ) )
    {}

    ~vertex_array() {
      glDeleteVertexArrays( n, &id );
    }

   public:
    __forceinline void bind() const  {
      glBindVertexArray( id );
    }
    __forceinline void unbind() const  {
      glBindVertexArray( 0 );
    }

  };

}


