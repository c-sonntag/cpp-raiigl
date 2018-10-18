#include <raiigl/buffer_ubo.hpp>

#include <raiigl/conceptual/index_manager.hpp>

namespace raiigl {

  static raiigl::conceptual::index_manager buffer_ubo_indexed;

  uint buffer_ubo::new_binded_point_index()
  { return buffer_ubo_indexed.new_index(); }

  void buffer_ubo::free_binded_point_index( const uint index )
  { return buffer_ubo_indexed.free_index( index ); }

}


