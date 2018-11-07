#pragma once

#include <raiigl/classes/non_copyable.hpp>

#include <raiigl/conceptual/index_manager.hpp>

#include <raiigl/shader.hpp>
#include <raiigl/gl_types.hpp>

#include <GL/glew.h>

#include <glm/glm.hpp>

#include <string>
#include <set>
#include <istream>
#include <stdexcept>

namespace raiigl {

  struct program : public raiigl::classes::non_copyable
  {
   public:
    using shaders_p_t = std::set<raiigl::shader const *>;

   public:
    const GLuint id;
    const std::string description;

   protected:
    bool destroyed = false;

   private:
    __forceinline void attach_shader( const shader & s )
    { glAttachShader( id, s.id ); }

    template<typename... Args>
    __forceinline void attach_shader( const shader & s, const Args & ... args )
    { attach_shader( s ); attach_shader( args... ); }

   private:
    __forceinline void detach_shader( const shader & s )
    { glDetachShader( id, s.id ); }

    template<typename... Args>
    __forceinline void detach_shader( const shader & s, const Args & ... args )
    { detach_shader( s ); detach_shader( args... ); }

   private:
    void link_program();

   private:
    __forceinline void process_link( const shaders_p_t & shaders_p ) {
      for ( const raiigl::shader * const s : shaders_p ) if ( s ) attach_shader( *s );
      link_program();
      for ( const raiigl::shader * const s : shaders_p ) if ( s ) detach_shader( *s );
    }

    template<typename... Args>
    __forceinline void process_link( const Args & ... shaders ) {
      attach_shader( shaders... );
      link_program();
      detach_shader( shaders... );
    }

   public:
    __forceinline program( const std::string _description, const shaders_p_t & shaders_p ) :
      id( glCreateProgram() ), description( std::move( _description ) )
    { process_link( shaders_p ); }

    __forceinline program( const shaders_p_t & shaders_p ) :
      id( glCreateProgram() ), description( "unknown" )
    { process_link( shaders_p ); }

   public:
    template<typename... Args>
    __forceinline program( const std::string _description, const Args & ... shaders ) :
      id( glCreateProgram() ), description( std::move( _description ) )
    { process_link( shaders... ); }

    template<typename... Args>
    __forceinline program( const Args & ... shaders ) :
      id( glCreateProgram() ), description( "unknown" )
    { process_link( shaders... ); }

   public:
    __forceinline ~program() {
      if ( id > 0 ) glDeleteProgram( id );
      destroyed = true;
    }

   public:
    __forceinline program( program && p ) :
      id( std::move( p.id ) ),
      description( std::move( p.description ) ),
      destroyed( std::move( p.destroyed ) ),
      texture_indexed( std::move( p.texture_indexed ) )
    { const_cast<GLuint &>( p.id ) = 0; }

   public:
    __forceinline void use() const
    { glUseProgram( id ); }

    __forceinline void unuse() const
    { glUseProgram( 0 ); }

   public:
    //__forceinline GLint get_uniform_location( const char * const var_cstr ) const {
    //  const GLint v( glGetUniformLocation( id, var_cstr ) );
    //  if ( v < 0 )
    //    throw std::runtime_error( "Impossible to get '" + std::string( var_cstr ) + "' into shader_pack" );
    //  return static_cast<GLint>( v ) ;
    //}
    //__forceinline GLint get_uniform_location( const std::string & var ) const
    //{ return get_uniform_location( var.c_str() ); }

    __forceinline GLint get_uniform_location( const std::string & var ) const {
      const GLint v( glGetUniformLocation( id, var.c_str() ) );
      if ( v < 0 )
        throw std::runtime_error( "Impossible to get '" + var + "' into shader_pack(" + description + ")" );
      return static_cast<GLint>( v ) ;
    }


   public:
    // template <typename TUniformType>
    // static __forceinline typename std::enable_if < ( sizeof( TUniformType ) <= sizeof( TUniformType * ) ), void >::type
    // set_uniform_value( const GLint, const TUniformType );
    //
    // template <typename TUniformType>
    // static __forceinline typename std::enable_if < ( sizeof( TUniformType ) > sizeof( TUniformType * ) ), void >::type
    // set_uniform_value( const GLint, const TUniformType & );

    static __forceinline void set_uniform_value( const GLint id, const float v )  { glUniform1f( id, v ); }
    static __forceinline void set_uniform_value( const GLint id, const int v )    { glUniform1i( id, v ); }
    static __forceinline void set_uniform_value( const GLint id, const uint v )   { glUniform1ui( id, v ); }

    static __forceinline void set_uniform_value( const GLint id, const textures_num num ) { glUniform1i( id, static_cast<int>( num ) - static_cast<int>( textures_num::Texture00 ) ); }

    static __forceinline void set_uniform_value( const GLint id, const glm::vec2 & v )   { glUniform2fv( id, 1, &v[0] ); }
    static __forceinline void set_uniform_value( const GLint id, const glm::vec3 & v )   { glUniform3fv( id, 1, &v[0] ); }
    static __forceinline void set_uniform_value( const GLint id, const glm::vec4 & v )   { glUniform4fv( id, 1, &v[0] ); }
    static __forceinline void set_uniform_value( const GLint id, const glm::mat4x4 & v ) { glUniformMatrix4fv( id, 1, GL_FALSE, &v[0][0] ); }

   public:
    // template <typename TUniformType>
    // __forceinline typename std::enable_if < ( sizeof( TUniformType ) <= sizeof( TUniformType * ) ), void >::type
    // set_uniform_value( const char * const var_name_cstr, const TUniformType value ) const
    // { program::set_uniform_value( get_uniform_location( var_name_cstr ), value ); }
    //
    // template <typename TUniformType>
    // __forceinline typename std::enable_if < ( sizeof( TUniformType ) > sizeof( TUniformType * ) ), void >::type
    // set_uniform_value( const char * const var_name_cstr, const TUniformType & value ) const
    // { program::set_uniform_value( get_uniform_location( var_name_cstr ), value ); }

    //template <typename TUniformType>
    //__forceinline typename std::enable_if < ( sizeof( TUniformType ) <= sizeof( TUniformType * ) ), void >::type
    //set_uniform_value( const std::string & var_name, const TUniformType value ) const
    //{ program::set_uniform_value( get_uniform_location( var_name ), value ); }
    //
    //template <typename TUniformType>
    //__forceinline typename std::enable_if < ( sizeof( TUniformType ) > sizeof( TUniformType * ) ), void >::type
    //set_uniform_value( const std::string & var_name, const TUniformType & value ) const
    //{ program::set_uniform_value( get_uniform_location( var_name ), value ); }

    template<typename ... TUniformsTypes>
    __forceinline void set_uniform_value( const std::string & var_name, const TUniformsTypes & ... values ) const
    { program::set_uniform_value( get_uniform_location( var_name ), values... ); }

   protected:
    raiigl::conceptual::index_manager texture_indexed
    {
      static_cast<uint>( raiigl::textures_num::Texture30 ),
      static_cast<uint>( raiigl::textures_num::Texture10 )
    };

   public:
    __forceinline raiigl::textures_num new_texture_index()
    { return raiigl::textures_num( texture_indexed.new_index() ); }

    __forceinline void mark_texture_index( const raiigl::textures_num index )
    { texture_indexed.free_index( uint( index ) ); }

    /** @todo never be used ? make raiigl free index */
    __forceinline void free_texture_index( const raiigl::textures_num index )
    { texture_indexed.free_index( uint( index ) ); }



  };

  // ---- ---- ---- ----

  //#define program__set_uniform_value__note "\"" + std::string( typeid( TUniformType ).name() ) + "\" in  with (" + std::string("value_size=" + std::to_string(sizeof( TUniformType )) + "  constref_size=" + std::to_string(sizeof( const TUniformType & ))+ "  constpointer_size=" + std::to_string(sizeof( const TUniformType * ) ) + ")" )
  //
  //  template <typename TUniformType>
  //  __forceinline typename std::enable_if < ( sizeof( TUniformType ) <= sizeof( TUniformType * ) ), void >::type
  //  program::set_uniform_value( const GLint, const TUniformType )
  //  { throw std::runtime_error( "[raiigl::program::set_uniform_value] Unknown const value type " program__set_uniform_value__note );}
  //
  //  template <typename TUniformType>
  //  __forceinline typename std::enable_if < ( sizeof( TUniformType ) > sizeof( TUniformType * ) ), void >::type
  //  program::set_uniform_value( const GLint, const TUniformType & )
  //  { throw std::runtime_error( "[raiigl::program::set_uniform_value] Unknown const ref type " program__set_uniform_value__note );}

  //template<typename TUniformType>
  //__forceinline TUniformType program::get()
  //{ throw std::runtime_error( "uniform_variable Unknown type " + std::string( typeid( TUniformType ).name() ) );}

  //template<typename TUniformType>
  //__forceinline void program::set( TUniformType v )
  //{ throw std::runtime_error( "uniform_variable Unknown type " + std::string( typeid( TUniformType ).name() ) + " in set method" );}
  //
  //template<typename TUniformType>
  //__forceinline void program::set( const TUniformType & v )
  //{ throw std::runtime_error( "uniform_variable Unknown const ref type " + std::string( typeid( TUniformType ).name() ) + " in set method" );}


  // ---- ---- ---- ----

  // template<> __forceinline void program::set_uniform_value( const GLint id, const float v )  { glUniform1f( id, v ); }
  // template<> __forceinline void program::set_uniform_value( const GLint id, const int v )    { glUniform1i( id, v ); }
  // template<> __forceinline void program::set_uniform_value( const GLint id, const uint v )   { glUniform1ui( id, v ); }
  //
  // 32bits pointer size dif
  //template<> __forceinline void uniform_variable::set( glm::vec2 v ) const { glUniform2f( id, v.x, v.y ); }

  // ----

  // template<> __forceinline void program::set_uniform_value( const GLint id, const glm::vec3 & v )         { glUniform3fv( id, 1, &v[0] ); }
  // template<> __forceinline void program::set_uniform_value( const GLint id, const glm::vec4 & v )         { glUniform4fv( id, 1, &v[0] ); }
  // template<> __forceinline void program::set_uniform_value( const GLint id, const glm::highp_mat4x4 & v ) { glUniformMatrix4fv( id, 1, GL_FALSE, &v[0][0] ); }

}


// Include ipp file
#include <raiigl/ipp/program.ipp>



