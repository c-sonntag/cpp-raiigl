#pragma once

#include <raiigl/classes/non_copyable_movable.hpp>

#include <raiigl/buffer.hpp>
#include <raiigl/gl430.hpp>

#include <raiigl/program.hpp>

#include <GL/glew.h>

#include <set>
#include <cstring>

namespace raiigl {

  struct buffer_ubo : public raiigl::buffer
  {
   protected:
    static std::set<uint> binded_points_index;

   public:
    static uint new_binded_point_index();
    static void free_binded_point_index( const uint index );

   public:
    static __forceinline uint get_max_bindings()
    { GLint max( 0 ); glGetIntegerv( GL_MAX_UNIFORM_BUFFER_BINDINGS, &max ); return uint( max );  }

   public:
    uint current_bind_buffer_base;

   protected:
    bool do_free_binded_point_at_destruct;

   public:
    buffer_ubo( const buffer_usage _usage = buffer_usage::DynamicDraw, const GLsizei _n = 1 ):
      buffer( buffer_type::Uniform, std::move( _usage ), std::move( _n ) ),
      current_bind_buffer_base( new_binded_point_index() ), do_free_binded_point_at_destruct( true )
    { raiigl::gl330::check_compatibility(); assign_base(); }

    buffer_ubo( const uint binding_point, const uint buffer_offset, const uint buffer_size, const buffer_usage _usage = buffer_usage::StaticDraw, const GLsizei _n = 1 ):
      buffer( buffer_type::Uniform, std::move( _usage ), std::move( _n ) ),
      current_bind_buffer_base( binding_point ), do_free_binded_point_at_destruct( false )
    { raiigl::gl330::check_compatibility(); assign_range_block( buffer_offset, buffer_size ); }

   public:
    ~buffer_ubo()
    { if ( do_free_binded_point_at_destruct ) free_binded_point_index( current_bind_buffer_base ); }

   protected:
    __forceinline void assign_base() const
    { glBindBufferBase( GL_UNIFORM_BUFFER, current_bind_buffer_base, id ); }

    __forceinline void assign_range_block( uint offset, uint size ) const
    { glBindBufferRange( GL_UNIFORM_BUFFER, current_bind_buffer_base, id, GLintptr( offset ), GLsizeiptr( size ) );  }

    //__forceinline void bind_base( raiigl::program & p, const char * ubo_name ) const {
    //  GLuint index = glGetUniformBlockIndex( p.id, ubo_name );
    //  bind_base( index );
    //}

   public:
    __forceinline void block_binding( raiigl::program & p, const GLuint index ) const
    { glUniformBlockBinding( p.id, index, current_bind_buffer_base ); }

    __forceinline void block_binding( raiigl::program & p, const char * ubo_name ) const {
      GLuint index = glGetUniformBlockIndex( p.id, ubo_name );
      block_binding( p, index );
    }

   public:
    void * map_buffer( const buffer_mode mode )
    { return glMapBuffer( GL_UNIFORM_BUFFER, GLenum( mode ) ); }

    void unmap_buffer()
    { glUnmapBuffer( GL_UNIFORM_BUFFER ); }

   public:
    template<typename TData>
    void memcpy_write_block( const TData & data )
    { memcpy( map_buffer( buffer_mode::WriteOnly ), &data, sizeof( TData ) ); unmap_buffer(); }


  };

}


