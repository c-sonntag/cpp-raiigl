#pragma once

#include <raiigl/program.hpp>

#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>

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
      const std::string error_message_str( error_message.data() );

      //
      std::ostringstream oss;
      oss << "Error during glsl program linking : " << std::endl;
      oss << "  --- (log_length : " << info_log_length << ") ---  " << std::endl
          << "  " + error_message_str << std::endl
          << "  --- ---  " << std::endl;
      if ( info_log_length == 0 )
        oss << "  (log_length==0 : possible non-debug mode on GPU ...)" << std::endl;

      //
      throw std::runtime_error( oss.str() );

    }
  }

}
