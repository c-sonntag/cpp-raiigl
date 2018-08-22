#pragma once

#include <raiigl/classes/non_copyable.hpp>

#include <raiigl/program.hpp>
#include <glm/glm.hpp>

#include <type_traits>

namespace raiigl {

  struct uniform_variable : public classes::non_copyable
  {
   public:
    // const raiigl::program & program;
    const std::string name;
    const GLint id;

   public:
    __forceinline uniform_variable( const raiigl::program & program, const std::string _name ) :
      // program( _program ),
      name( std::move( _name ) ),
      id( program.get_uniform_location( name ) )
    {}

   public:
    template<typename ... Args>
    __forceinline void set( const Args & ... args ) const
    { program::set_uniform_value( id, args... ); }

    //template<typename TUniformTypeT> void setByCopy( TUniformTypeT v ) const;
    //template<typename TUniformTypeT> void setByRef( const TUniformTypeT & v ) const;

  };

  // ---- ---- ---- ----

  template<typename TUniformType>
  struct uniform_variable_stored : public uniform_variable
  {
   public:
    TUniformType var;

   public:
    uniform_variable_stored( const raiigl::program & _program, const std::string & _name, TUniformType initial_value = 1 ) :
      uniform_variable( _program, _name ),
      var( initial_value )
    {}

   public:
    __forceinline void send() const { set<TUniformType>( var ); }

   public:
    __forceinline void inc() { ++var; send(); }
    __forceinline void dec() { --var; send(); }

   public:
    using TOp = uniform_variable_stored<TUniformType>;
    TOp & operator=( TUniformType v ) { var = v; send(); return *this; }
    TOp & operator+=( TUniformType v ) { var += v; send(); return *this; }
    TOp & operator-=( TUniformType v ) { var -= v; send(); return *this; }
    TOp & operator++() { ++var; send(); return *this; }
    TOp & operator--() { --var; send(); return *this; }
  };

}


