#include <raiigl/buffer.hpp>

namespace raiigl {

  std::unordered_set<buffer_type> buffer::binded_buffer_type;

  void buffer::unbind_all_binded_buffer_type()
  {
    for ( const buffer_type type : binded_buffer_type )
      glBindBuffer( static_cast<GLenum>( type ), 0 );
    binded_buffer_type.clear();
  }


}


