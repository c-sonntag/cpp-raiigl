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
    const GLuint id;

   protected:
    bool invalid_state = false;

   private:
    __forceinline GLuint gen_vertex_array()
    {
      GLuint id;
      glGenVertexArrays( 1, &id );
      return id;
    }

   public:
    vertex_array() :
      id( gen_vertex_array() )
    {}

    ~vertex_array()
    {
      if( (id > 0) && !invalid_state ) glDeleteVertexArrays( 1, &id );
      invalid_state = true;
    }

   public:
    __forceinline vertex_array( vertex_array&& vao ) :
      id( std::move( vao.id ) ),
      invalid_state( std::move( vao.invalid_state ) )
    { const_cast<GLuint&>( vao.id ) = 0; vao.invalid_state = true; }

   public:
    __forceinline void bind() const
    {
      glBindVertexArray( id );
    }
    __forceinline void unbind() const
    {
      glBindVertexArray( 0 );
    }

   public:
    //__forceinline void attrib( raiigl::buffer & buffer, const GLuint index, const uint size, const raiigl::data_type type, const bool normalize_it_from_data_type = false, const GLsizei stride = 0, const void * const pointer = nullptr ) const
    //{
    //  buffer.bind();
    //  glVertexAttribPointer( index, static_cast<GLint>(size), static_cast<GLenum>( type ), normalize_it_from_data_type, stride, pointer );
    //}

    __forceinline void attrib( raiigl::buffer& buffer, const GLuint index, const uint size, const raiigl::data_type type, const bool normalize_it_from_data_type = false, const uint stride = 0, const uint buffer_decal = 0 ) const
    {
      glEnableVertexAttribArray( index );
      buffer.bind();
      glVertexAttribPointer( index, static_cast<GLint>( size ), static_cast<GLenum>( type ), normalize_it_from_data_type, static_cast<GLsizei>( stride ), reinterpret_cast<void*>( buffer_decal ) );
    }

    __forceinline void unattrib( const GLuint index )
    { glDisableVertexAttribArray( index ); }

   public:
    __forceinline void set_divisor( const GLuint index, GLuint divisor )
    { glVertexAttribDivisor( index, divisor ); }


  };

}


