#pragma once

#include <raiigl/types.hpp>
#include <raiigl/gl_types.hpp>

#include <raiigl/classes/non_copyable.hpp>

#include <GL/glew.h>

#include <bits/move.h>
#include <stdexcept>

namespace raiigl {

#define raiigl_glew_throw_check(v) {if ( !v ) throw std::runtime_error( "Current GLEW Instance not support: " # v );}

  struct gl330 : public classes::non_copyable
  {
    static __forceinline void check_compatibility() { raiigl_glew_throw_check( GLEW_VERSION_3_3 ); }

    __forceinline void draw_arrays( const primitive_type mode, const uint first, const uint count ) const
    { glDrawArrays( static_cast<GLenum>( mode ), static_cast<GLsizei>( first ), static_cast<GLsizei>( count ) ); }

    __forceinline void draw_elements( const primitive_type mode, const uint count, const void * const indices = nullptr, const indice_type type = raiigl::indice_type::Uint ) const
    { glDrawElements( static_cast<GLenum>( mode ), static_cast<GLsizei>( count ), static_cast<GLenum>( type ), indices ); }

    __forceinline void draw_elements_base_vertex( const primitive_type mode, const uint count, const GLint base_vertex, void * const indices = nullptr, const indice_type type = raiigl::indice_type::Uint ) const
    { glDrawElementsBaseVertex( static_cast<GLenum>( mode ), static_cast<GLsizei>( count ), static_cast<GLenum>( type ), indices, base_vertex ); }

    // ---- ----

    __forceinline void draw_arrays_instanced( const primitive_type mode, const uint first, const uint count, const uint primcount ) const
    { glDrawArraysInstanced( static_cast<GLenum>( mode ), static_cast<GLsizei>( first ), static_cast<GLsizei>( count ), static_cast<GLsizei>( primcount ) ); }

    __forceinline void draw_elements_instanced( const primitive_type mode, const uint count, const uint primcount, const void * const indices = nullptr, const indice_type type = raiigl::indice_type::Uint ) const
    { glDrawElementsInstanced( static_cast<GLenum>( mode ), static_cast<GLsizei>( count ), static_cast<GLenum>( type ), indices, static_cast<GLsizei>( primcount ) ); }

    // ---- ----

    __forceinline void enable_vertex_attrib_array( const GLuint index ) const
    { glEnableVertexAttribArray( index ); }

    __forceinline void disable_vertex_attrib_array( const GLuint index ) const
    { glDisableVertexAttribArray( index ); }

    __forceinline void vertex_attrib_pointer( const GLuint index, const GLint size, const data_type type, const bool normalize_it_from_data_type = false, const GLsizei stride = 0, const void * const pointer = nullptr ) const
    { glVertexAttribPointer( index, size, static_cast<GLenum>( type ), normalize_it_from_data_type, stride, pointer ); }

    // ---- ----

    __forceinline void enable( const gl_capabilities cap ) const
    { glEnable( static_cast<GLenum>( cap ) ); }

    __forceinline bool is_enable( const gl_capabilities cap ) const
    { return glIsEnabled( static_cast<GLenum>( cap ) ); }

    __forceinline void disable( const gl_capabilities cap ) const
    { glDisable( static_cast<GLenum>( cap ) ); }

    // ---- ----

    __forceinline void blend_func( const blend_func_type sfactor = blend_func_type::One, const blend_func_type dfactor = blend_func_type::Zero ) const
    { glBlendFunc( static_cast<GLenum>( sfactor ), static_cast<GLenum>( dfactor ) ); }

    __forceinline void depth_func( const deth_func_type func_type ) const
    { glDepthFunc( static_cast<GLenum>( func_type ) ); }

    // ---- ----

    __forceinline void activate_texture( const uint num ) const
    { glActiveTexture( GL_TEXTURE0 + num ); }

    __forceinline void activate_texture( const textures_num num ) const
    { glActiveTexture( static_cast<GLenum>( num ) ); }

    // ---- ----

  };

}

