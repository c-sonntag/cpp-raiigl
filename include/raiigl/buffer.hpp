#pragma once

#include <raiigl/classes/non_copyable.hpp>

#include <GL/glew.h>

#include <vector>
#include <array>
#include <unordered_set>

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

  enum class buffer_mode
  {
    ReadOnly = GL_READ_ONLY,
    WriteOnly = GL_WRITE_ONLY,
    ReadWrite = GL_READ_WRITE,
  };

  // ---- ---- ---- ----

  struct buffer : public classes::non_copyable
  {
   public:
    static std::unordered_set<buffer_type> binded_buffer_type;
    static void unbind_all_binded_buffer_type();

   public:
    const buffer_type type;
    const buffer_usage usage;

   public:
    const GLuint id;

   private:
    __forceinline GLuint gen_buffer()  {
      GLuint id;
      glGenBuffers( 1, &id );
      return id;
    }

   public:
    buffer( const buffer_type _type = buffer_type::Array, const buffer_usage _usage = buffer_usage::StaticDraw ):
      type( std::move( _type ) ),
      usage( std::move( _usage ) ),
      id( gen_buffer() )
    {}

    __forceinline ~buffer()
    { glDeleteBuffers( 1, &id ); }

   public:
    __forceinline void bind() const
    { glBindBuffer( static_cast<GLenum>( type ), id ); binded_buffer_type.insert( type ); }

    __forceinline void unbind() const
    { glBindBuffer( static_cast<GLenum>( type ), 0 ); binded_buffer_type.erase( type ); }

   public:
    __forceinline void send( const size_t byte_size, const GLvoid * const data ) const  {
      glBufferData(
        static_cast<GLenum>( type ),
        static_cast<GLsizeiptr>( byte_size ),
        data,
        static_cast<GLenum>( usage )
      );
    }

    __forceinline void update( const size_t byte_size, const GLvoid * const data, const size_t offset = 0 ) const  {
      glBufferSubData(
        static_cast<GLenum>( type ),
        GLintptr( offset ),
        static_cast<GLsizeiptr>( byte_size ),
        data
      );
    }

   public:
    struct struct_wrapper
    {
      const size_t byte_size;
      const GLvoid * const data;

      template<typename TData> __forceinline
      struct_wrapper( const TData & data ) : byte_size( sizeof( TData ) ), data( &data ) {}

      template<typename TType> __forceinline
      struct_wrapper( const std::vector<TType> & vec ) : byte_size( vec.size() * sizeof( TType ) ), data( vec.data() ) {}

      template<typename TType, std::size_t TSize> __forceinline
      struct_wrapper( const std::array<TType, TSize> & arr ) : byte_size( TSize * sizeof( TType ) ), data( arr.data() ) {}

      template<typename TType, std::size_t TSize> __forceinline
      struct_wrapper( const TType( &carray )[TSize] ) : byte_size( TSize * sizeof( TType ) ), data( carray ) {}
    };

   public:
    void send( const struct_wrapper & sw ) const
    { send( sw.byte_size, sw.data ); }

    void update( const struct_wrapper & sw, const size_t offset = 0 ) const
    { update( sw.byte_size, sw.data, offset ); }


   public:
    __forceinline void bind_and_send( const size_t byte_size, const GLvoid * const data ) const { bind(); send( byte_size, data ); }
    __forceinline void bind_and_send( const struct_wrapper & sw ) const { bind(); send( sw ); }

   public:
    __forceinline void bind_and_update( const size_t byte_size, const GLvoid * const data, const size_t offset = 0 ) const { bind(); update( byte_size, data, offset ); }
    __forceinline void bind_and_update( const struct_wrapper & sw, const size_t offset = 0 ) const { bind(); update( sw, offset ); }

    //   public:
    //    template<typename TData> __forceinline void send( const TData & data )
    //    { send( sizeof( TData ), &data ); }

    //    template<typename TType> __forceinline void send( const std::vector<TType> & vec ) const
    //    { send( vec.size() * sizeof( TType ), vec.data() ); }

    //    template<typename TType, std::size_t TSize> __forceinline void send( const std::array<TType, TSize> & arr ) const
    //    { send( TSize * sizeof( TType ), arr.data() ); }

    //    template<typename TType, std::size_t TSize> __forceinline void send( const TType( &carray )[TSize] ) const
    //    { send( TSize * sizeof( TType ), carray ); }

    //   public:
    //    template<typename TData> __forceinline void update( const TData & data, const size_t offset = 0 )
    //    { update( sizeof( TData ), &data, offset ); }

    //    template<typename TType> __forceinline void update( const std::vector<TType> & vec, const size_t offset = 0 ) const
    //    { update( vec.size() * sizeof( TType ), vec.data(), offset ); }

    //    template<typename TType, std::size_t TSize> __forceinline void update( const std::array<TType, TSize> & arr, const size_t offset = 0 ) const
    //    { update( TSize * sizeof( TType ), arr.data(), offset ); }

    //    template<typename TType, std::size_t TSize> __forceinline void update( const TType( &carray )[TSize], const size_t offset = 0 ) const
    //    { update( TSize * sizeof( TType ), carray, offset ); }

    //   public:
    //    __forceinline void bind_and_send( const size_t byte_size, const GLvoid * const data ) const                                 { bind(); send( byte_size, data ); }
    //    template<typename TData> __forceinline void bind_and_send( const TData & data, const size_t offset = 0 )                    { bind(); send( data ); }
    //    template<typename TType> __forceinline void bind_and_send( const std::vector<TType> & vec ) const                           { bind(); send( vec ); }
    //    template<typename TType, std::size_t TSize> __forceinline void bind_and_send( const std::array<TType, TSize> & arr ) const  { bind(); send( arr ); }
    //    template<typename TType, std::size_t TSize> __forceinline void bind_and_send( const TType( &carray )[TSize] ) const         { bind(); send( carray ); }

    //   public:
    //    __forceinline void bind_and_update( const size_t byte_size, const GLvoid * const data, const size_t offset = 0 ) const                                  { bind(); update( byte_size, data, offset ); }
    //    template<typename TData> __forceinline void bind_and_update( const TData & data, const size_t offset = 0 )                                              { bind(); update( data, offset ); }
    //    template<typename TType> __forceinline void bind_and_update( const std::vector<TType> & vec, const size_t offset = 0 ) const                            { bind(); update( vec, offset ); }
    //    template<typename TType, std::size_t TSize> __forceinline void bind_and_update( const std::array<TType, TSize> & arr, const size_t offset = 0 ) const   { bind(); update( arr, offset ); }
    //    template<typename TType, std::size_t TSize> __forceinline void bind_and_update( const TType( &carray )[TSize], const size_t offset = 0 ) const          { bind(); update( carray, offset ); }


  };

}


