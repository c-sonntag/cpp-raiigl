#pragma once

#include <raiigl/classes/non_copyable.hpp>

#include <raiigl/program.hpp>
#include <glm/glm.hpp>

#include <type_traits>
#include <vector>

namespace raiigl {

  struct uniform_variable_multiple : public classes::non_copyable
  {
   public:
    const std::string name;
    const std::vector<GLint> ids;

   private:
    std::vector<GLint> do_fill_uniform_locations( std::vector<GLint> & ids, const raiigl::program & program )
    { ids.emplace_back( program.get_uniform_location( name ) ); }

    template<typename ... Args>
    std::vector<GLint> do_fill_uniform_locations( std::vector<GLint> & ids, const raiigl::program & program, const Args & ... programs )
    { ids.emplace_back( program.get_uniform_location( name ) ); do_fill_uniform_locations( ids, programs... ); }

    template<typename ... Args>
    std::vector<GLint> get_uniform_locations( const Args & ... programs ) {
      std::vector<GLint> ids;
      ids.reserve( sizeof( Args )... );
      do_fill_uniform_locations( ids, programs... );
    }

   public:
    template<typename ... Args>
    uniform_variable_multiple( const std::string & _name, const Args & ... programs ) :
      name( _name ),
      ids( get_uniform_locations( programs... ) )
    {}

   public:
    template<typename ... Args>
    __forceinline void set( const Args & ... args ) const
    { for ( const GLint id : ids ) program::set_uniform_value( id, args... ); }

  };

  // ---- ---- ---- ----

  template<typename TUniformType>
  struct uniform_variable_multiple_stored : public uniform_variable_multiple
  {
   public:
    TUniformType var;

   public:
    template<typename ... Args>
    uniform_variable_multiple_stored( const std::string & _name, TUniformType initial_value, const Args & ... programs ) :
      uniform_variable_multiple( _name, programs... ),
      var( initial_value )
    {}

   public:
    __forceinline void send() const { set<TUniformType>( var ); }

   public:
    __forceinline void inc() { ++var; send(); }
    __forceinline void dec() { --var; send(); }

   public:
    using TOp = uniform_variable_multiple_stored<TUniformType>;
    TOp & operator=( TUniformType v ) { var = v; send(); return *this; }
    TOp & operator+=( TUniformType v ) { var += v; send(); return *this; }
    TOp & operator-=( TUniformType v ) { var -= v; send(); return *this; }
    TOp & operator++() { ++var; send(); return *this; }
    TOp & operator--() { --var; send(); return *this; }
  };

}


