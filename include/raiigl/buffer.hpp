#pragma once

#include <raiigl/classes/non_copyable.hpp>

#include <GL/glew.h>

namespace raiigl {

  enum class buffer_type : GLenum
  {
    Array             = GL_ARRAY_BUFFER,
    AtomicCounter     = GL_ATOMIC_COUNTER_BUFFER,
    CopyRead          = GL_COPY_READ_BUFFER,
    CopyWrite         = GL_COPY_WRITE_BUFFER,
    DispatchIndirect  = GL_DISPATCH_INDIRECT_BUFFER,
    DrawIndirect      = GL_DRAW_INDIRECT_BUFFER,
    ElementArray      = GL_ELEMENT_ARRAY_BUFFER,
    PixelPack         = GL_PIXEL_PACK_BUFFER,
    PixelUnpack       = GL_PIXEL_UNPACK_BUFFER,
    Query             = GL_QUERY_BUFFER,
    ShaderStorage     = GL_SHADER_STORAGE_BUFFER,
    Texture           = GL_TEXTURE_BUFFER,
    TransformFeedback = GL_TRANSFORM_FEEDBACK_BUFFER,
    Uniform           = GL_UNIFORM_BUFFER
  };

  /**
   * The frequency of access may be one of these:
   *  STREAM :
   *   The data store contents will be modified once and used at most a few times.
   *  STATIC :
   *   The data store contents will be modified once and used many times.
   *  DYNAMIC :
   *   The data store contents will be modified repeatedly and used many times.
   *
   * The nature of access may be one of these:
   *  DRAW :
   *   The data store contents are modified by the application, and used as the source for GL drawing and image specification commands.
   *  READ :
   *   The data store contents are modified by reading data from the GL, and used to return that data when queried by the application.
   *  COPY :
   *   The data store contents are modified by reading data from the GL, and used as the source for GL drawing and image specification commands.
   */
  enum class buffer_usage : GLenum
  {
    StreamDraw  = GL_STREAM_DRAW,
    StreamRead  = GL_STREAM_READ,
    StreamCopy  = GL_STREAM_COPY,
    StaticDraw  = GL_STATIC_DRAW,
    StaticRead  = GL_STATIC_READ,
    StaticCopy  = GL_STATIC_COPY,
    DynamicDraw = GL_DYNAMIC_DRAW,
    DynamicRead = GL_DYNAMIC_READ,
    DynamicCopy = GL_DYNAMIC_COPY
  };

  struct buffer : public classes::non_copyable
  {
   public:
    const buffer_type type;
    const buffer_usage usage;
    const GLsizei n;

   public:
    const GLuint id;

   private:
    __forceinline GLuint gen_buffer( const GLsizei n )  {
      GLuint id;
      glGenBuffers( n, &id );
      return id;
    }

   public:
    buffer( const buffer_type _type = buffer_type::Array, const buffer_usage _usage = buffer_usage::StaticDraw, const GLsizei _n = 1 ):
      type( std::move( _type ) ),
      usage( std::move( _usage ) ),
      n( std::move( _n ) ),
      id( gen_buffer( n ) )
    {}

    __forceinline ~buffer()
    { glDeleteBuffers( n, &id ); }

   public:
    __forceinline void bind() const
    { glBindBuffer( static_cast<GLenum>( type ), id ); }

    __forceinline void unbind() const
    { glBindBuffer( static_cast<GLenum>( type ), 0 ); }

   public:
    void send( const size_t size, const GLvoid * const data ) const  {
      glBufferData(
        static_cast<GLenum>( type ),
        static_cast<GLsizeiptr>( size ),
        data,
        static_cast<GLenum>( usage )
      );
    }

    __forceinline void bind_and_send( const size_t size, const GLvoid * const data ) const {
      bind();
      send( size, data );
    }

  };

}


