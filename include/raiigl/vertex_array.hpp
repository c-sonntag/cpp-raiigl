#pragma once

#include <raiigl/classes/non_copyable.hpp>

#include <raiigl/types.hpp>
#include <raiigl/gl_types.hpp>
#include <raiigl/buffer.hpp>

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

   public:
    //__forceinline void attrib( raiigl::buffer & buffer, const GLuint index, const uint size, const raiigl::data_type type, const bool normalize_it_from_data_type = false, const GLsizei stride = 0, const void * const pointer = nullptr ) const
    //{
    //  buffer.bind();
    //  glVertexAttribPointer( index, static_cast<GLint>(size), static_cast<GLenum>( type ), normalize_it_from_data_type, stride, pointer );
    //}

    __forceinline void attrib( raiigl::buffer & buffer, const GLuint index, const uint size, const raiigl::data_type type, const bool normalize_it_from_data_type = false, const GLsizei stride = 0, const uint buffer_decal = 0 ) const {
      glEnableVertexAttribArray( index );
      buffer.bind();
      glVertexAttribPointer( index, static_cast<GLint>( size ), static_cast<GLenum>( type ), normalize_it_from_data_type, stride, reinterpret_cast<void *>( buffer_decal ) );
    }

    __forceinline void unattrib( const GLuint index ) {
      glDisableVertexAttribArray( index );
    }


  };

}


