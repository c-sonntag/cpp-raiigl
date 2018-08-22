#pragma once

#include <raiigl/types.hpp>
#include <raiigl/shader.hpp>

#include <stdexcept>

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>

#include <cstdlib>
#include <cstring>


namespace raiigl {


  inline std::string get_shader_type_name( shader_type type )
  {
    if ( type == shader_type::Vertex ) return "Vertex";
    else if ( type == shader_type::Fragment ) return "Fragment";
    else if ( type == shader_type::Compute ) return "Compute";
    else return "unknown";
  }

  // ---- ---- ---- ----

  inline shader::shader( const std::string & code, shader_type _type ) :
    type( std::move( _type ) ),
    id( glCreateShader( static_cast<GLuint>( type ) ) )
  {
    // Compile it
    const char * const code_cstr[1] {code.data()};
    const GLint code_length[1] { static_cast<GLint>( code.size() ) };

    glShaderSource( id, 1, code_cstr, code_length );
    glCompileShader( id );

    // Check
    int compile_status_result = GL_FALSE;
    int info_log_length { 0 };
    glGetShaderiv( id, GL_COMPILE_STATUS, &compile_status_result );
    glGetShaderiv( id, GL_INFO_LOG_LENGTH, &info_log_length );
    if ( compile_status_result == GL_FALSE )
    {
      std::vector<char> error_message( static_cast<uint>( info_log_length ) + 1 );
      glGetShaderInfoLog( id, info_log_length, nullptr, error_message.data() );
      error_message[static_cast<size_t>( info_log_length )] = '\0';
      const std::string error_message_str( error_message.data() );

      //
      std::string code_without_carrier (code);
      std::replace( code_without_carrier.begin(), code_without_carrier.end(), '\r', ' ' );

      std::ostringstream oss;
      oss << "Error during '" << get_shader_type_name( type ) << "' shader compilation : " << std::endl
          << "  " + error_message_str << std::endl
          << " Source shader : " << std::endl
          << "  -------  " << std::endl
          << code_without_carrier << std::endl
          << "  -------  " << std::endl;
      //
      throw std::runtime_error( oss.str() );
    }

  }

  // ---- ---- ---- ----

  inline std::string shader::to_string( std::istream & code_stream )
  {
    std::string code_str;

    if ( ! code_stream.good() )
      throw std::runtime_error( "Impossible to parse stream." );

    std::string line;
    while ( getline( code_stream, line ) )
      code_str += "\n" + line;

    return code_str;
  }


}
