#include <raiigl/buffer_ubo.hpp>

namespace raiigl {

  std::set<uint> buffer_ubo::binded_points_index;

  // ---- ----

  uint buffer_ubo::new_binded_point_index()
  {
    for ( uint bpi( 0 ); ; ++bpi )
    {
      if ( binded_points_index.find( bpi ) != binded_points_index.end() )
      { binded_points_index.insert( bpi ); return bpi; }
    }
  }

  // ---- ----

  void buffer_ubo::free_binded_point_index( const uint index )
  {
    binded_points_index.erase( index );
  }


}


