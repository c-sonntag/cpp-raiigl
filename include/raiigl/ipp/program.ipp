#pragma once

#include <raiigl/program.hpp>

#include <stdexcept>
#include <string>
#include <vector>

namespace raiigl {

  inline void program::link_program()
  {
    // Link the program
    glLinkProgram( id );

    // Check the program
    int link_status_result = GL_FALSE;
    int info_log_length {0};
    glGetProgramiv( id, GL_LINK_STATUS, &link_status_result );
    glGetProgramiv( id, GL_INFO_LOG_LENGTH, &info_log_length );
    if ( link_status_result == GL_FALSE )
    {
      std::vector<char> error_message( static_cast<uint>( info_log_length ) + 1 );
      glGetProgramInfoLog( id, info_log_length, nullptr, error_message.data() );
      error_message[static_cast<size_t>( info_log_length )] = '\0';
      throw std::runtime_error( "Error during program linking : " + std::string( error_message.data() ) );
    }
  }

}
