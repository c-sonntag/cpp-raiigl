#pragma once

#include <raiigl/classes/non_copyable.hpp>

#include <raiigl/program.hpp>
#include <glm/glm.hpp>

#include <type_traits>
#include <vector>

/**
 * In wainting of real use
 * Need https://www.khronos.org/opengl/wiki/GLAPI/glProgramUniform 
 *   Or ARB_separate_shader_objects 
 *   to impl for multiple program
 * More about https://www.khronos.org/opengl/wiki/GLSL_:_common_mistakes#glUseProgram
 * And other https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glProgramUniform.xhtml
 */


namespace raiigl {

  struct uniform_variable_multiple : public classes::non_copyable
  {
   public:
    struct vector_of_uniform_locations : public std::vector<GLint>
    {
      void do_fill_uniform_locations( const std::string & name, const raiigl::program & program )
      { emplace_back( program.get_uniform_location( name ) ); }

      template<typename ... Args>
      void do_fill_uniform_locations( const std::string & name, const raiigl::program & program, const Args & ... programs )
      { emplace_back( program.get_uniform_location( name ) ); do_fill_uniform_locations( name, programs... ); }

      template<typename ... Args>
      vector_of_uniform_locations( const std::string & name, const Args & ... programs ) {
        reserve( sizeof...( Args ) );
        do_fill_uniform_locations( name, programs... );
      }
    };

   public:
    const std::string name;
    const vector_of_uniform_locations ids;

   public:
    template<typename ... Args>
    uniform_variable_multiple( const std::string _name, const Args & ... programs ) :
      name( std::move( _name ) ),
      ids( name, programs... )
    {}

   public:
    template<typename ... Args>
    __forceinline void set( const Args & ... args ) const
    { for ( const GLint id : ids ) program::set_uniform_value( id, args... ); }

  };

  // ---- ---- ---- ----

  template<typename TUniformType>
  struct uniform_variable_stored_multiple : public uniform_variable_multiple
  {
   public:
    TUniformType var;

   public:
    template<typename ... Args>
    uniform_variable_stored_multiple( const std::string & _name, TUniformType initial_value, const Args & ... programs ) :
      uniform_variable_multiple( _name, programs... ),
      var( initial_value )
    {}

   public:
    __forceinline void send() const { set<TUniformType>( var ); }

   public:
    __forceinline void inc() { ++var; send(); }
    __forceinline void dec() { --var; send(); }

   public:
    using TOp = uniform_variable_stored_multiple<TUniformType>;
    TOp & operator=( TUniformType v ) { var = v; send(); return *this; }
    TOp & operator+=( TUniformType v ) { var += v; send(); return *this; }
    TOp & operator-=( TUniformType v ) { var -= v; send(); return *this; }
    TOp & operator++() { ++var; send(); return *this; }
    TOp & operator--() { --var; send(); return *this; }
  };

}


