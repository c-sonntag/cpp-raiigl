#pragma once

#include <raiigl/gl330.hpp>

namespace raiigl {

  struct gl420 : public gl330
  {
    struct draw_arrays_indirect_command
    {
      uint  count = 0, prim_count = 0, first = 0, base_instance = 0;
      draw_arrays_indirect_command() = default;
      inline draw_arrays_indirect_command( const uint _count, const uint _prim_count, const uint _first, const uint _base_instance ):
        count( std::move( _count ) ), prim_count( std::move( _prim_count ) ),
        first( std::move( _first ) ), base_instance( std::move( _base_instance ) )
      {}
    };

    static constexpr __forceinline void check_compatibility() { raiigl_glew_throw_check( GLEW_VERSION_4_2 ); }

    __forceinline void draw_arrays_instanced_base_instance( const primitive_type mode, const GLuint first, const GLuint count, const GLuint primcount, const GLuint baseinstance ) const
    { glDrawArraysInstancedBaseInstance( static_cast<GLenum>( mode ), static_cast<GLint>( first ), static_cast<GLsizei>( count ), static_cast<GLsizei>( primcount ), baseinstance ); }

    __forceinline void draw_arrays_instanced_base_instance( const primitive_type mode, const draw_arrays_indirect_command & cmd ) const
    { glDrawArraysInstancedBaseInstance( static_cast<GLenum>( mode ), static_cast<GLint>( cmd.first ),  static_cast<GLsizei>( cmd.count ), static_cast<GLsizei>( cmd.prim_count ), cmd.base_instance ); }

  };

  // ---- ---- ---- ----

  __forceinline bool operator==( const gl420::draw_arrays_indirect_command & lhs, const gl420::draw_arrays_indirect_command & rhs )
  { return lhs.count == rhs.count && lhs.prim_count == rhs.prim_count && lhs.first == rhs.first && lhs.base_instance == rhs.base_instance; }

  __forceinline bool operator!=( const gl420::draw_arrays_indirect_command & lhs, const gl420::draw_arrays_indirect_command & rhs )
  { return !( lhs == rhs ); }

}

