#pragma once

#include <ostream>

#include <raiigl/uniform_variable.hpp>


template<typename TUniformType>
std::ostream & operator<<( std::ostream & os, const raiigl::uniform_variable_stored<TUniformType> & gluvs )
{
  os << gluvs.var;
  return os;
}

